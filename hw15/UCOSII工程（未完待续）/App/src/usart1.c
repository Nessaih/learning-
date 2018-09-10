#include "usart1.h"
uint8 Rec_Buffer[MAX_LEN];
uint8 Usart1_Flag=0,Time_Out;//Usart1_FlagΪ0��ʾ����δ��ɣ�������գ�Ϊ1��ʾ������ɲ��������
uint16 LEN=0;
/********************************************************************************************
*  �� �� ���� Usart1_Init
*  ��    ��:  Usart1���ڳ�ʼ��
*  ��������� ��   
*  ��������� ��
*  �� �� ֵ:  ��
*  ��    ��:  ��ΰ
*  �������:  2018-07-20
*  ע������:  ��
********************************************************************************************/
void Usart1_Init(void)
{
	
	//�����ʷ�Ƶ�������
	double USART1DIV;
	uint16 DIV_Man,DIV_Frac,Over8;
	
	//I0�ڳ�ʼ��
	RCC->AHB1ENR |= 0X01;					//����PAʱ��
	GPIOA->MODER &=~ ((0X03<<18)|(0X03<20)); //PA9,PA10ģʽ����
	GPIOA->MODER |= ((0X02<<18)|(0X02<<20)); //PA9,PA10ѡ�ø��ù���
	
	GPIOA->OTYPER &=~ (0x01<<9);			//PA9�������
	GPIOA->OSPEEDR &=~ (0X03<<18); 			//PA9����ٶ�����
	GPIOA->OSPEEDR |= 0X01<<18; 			//PA9����ٶ�25MHz
	GPIOA->PUPDR &=~ (0X03<<18);				//PA9 ����ģʽ
	
	GPIOA->PUPDR &=~ (0X03<<20); 			//PA10��������
	GPIOA->PUPDR |= 0X01<<20; 				//PA10����
	
	GPIOA->AFR[1] &=~ ((0X0F<<4)|(0X0F<<8));			
	GPIOA->AFR[1] |= (0X07<<4)|(0X07<<8);	//PA9���ù���ѡ��TX,PA10���ù���ѡ��RX
	
	//USART1����
	RCC->APB2ENR |= 0X01<<4;				//USART1ʱ��ʹ��
	RCC->APB2RSTR |= 0X01<<4;				//USART1��λһ��
	RCC->APB2RSTR &=~ (0X01<<4);			//USART1����λ
	
	USART1->CR1 &=~ (0X01<<15|(0X01<<12));//16��������;�ֳ�8λ
	USART1->CR1 |=0X03<<2;					//���ͽ���ʹ��
	USART1->CR2 &=~(0X03<<12);				//һ��ֹͣλ
	
	//�������Զ�����
	Over8 = (USART1->CR1&0X01<<15)>>15;
	USART1DIV = FCK / (8*(2-Over8)*BAUD_RATE);
	DIV_Man = ((uint16)USART1DIV)<<4 ;
	DIV_Frac = (uint16)((USART1DIV-DIV_Man/16)*16 + 0.5);//+0.5��ʾ��������
	USART1->BRR = DIV_Man | DIV_Frac;
	
	//USART1->BRR = 0X222<<4 | 0X0E;		//�������ֶ�����9600
	
	USART1->CR1 |= (0X01<<5);//�����ж�ʹ�ܣ������ж�ʹ��
	USART1->SR &=~ (0X01<<5);//�жϱ�־λ���
	NVIC_SetPriorityGrouping(7-2); //����Ϊ��2��  
    NVIC_SetPriority(USART1_IRQn,NVIC_EncodePriority(7-2,0,0));//�������ȼ�
	NVIC_EnableIRQ(USART1_IRQn); 
	USART1->CR1 |= 0X01<<13;		//USART1ʹ��
	
}

void Byte_Send(uint8 Msg)
{
	uint32 delay = 0;
	while(!(USART1->SR&(0X01<<7))&&(delay<168000))//TXE=0��һ������û����,�ȴ�1us
	{
		delay++;
	}
	if(USART1->SR&(0X01<<7))//TXE=1��ʾ��һ�����ݴ���
		USART1->DR = Msg;

}

void Str_Send(uint8 Str[])
{
	uint16 i; 
	for(i=0;Str[i]!='\0';i++)
	{
		Byte_Send(Str[i]);
	}
}

uint8 Byte_Receive(void)
{
	uint8 Msg='\0';
	uint32 delay = 0;
	while(!(USART1->SR&(0X01<<5))&&(delay<1680))//RXNE=0��������δ���,�ȴ�0.01us
	{
		delay++;
	}
	if(USART1->SR&(0X01<<5))//RXNE=1 �������
		Msg=USART1->DR ;
	return Msg;

}


void USART1_IRQHandler(void)
{
	uint8 Receive_Data;
    if(USART1->SR & (0X01<<5))
    {
		Time_Out = 3;//˼����Time_Out = 3;���� if(Usart1_Flag == 0)�����������ʲô����
		Receive_Data = USART1->DR;
        if(Usart1_Flag == 0)
        {
            Rec_Buffer[LEN++] = Receive_Data;
        }
    }
}
void Led_Switch(void)
{
    if(Usart1_Flag)
    {
        Usart1_Flag = 0;
        Str_Send(Rec_Buffer); 
		Byte_Send('\n');
        if(strcmp((const char *)Rec_Buffer,"LED_ON") == 0)
        {
            Led_State_Control(0X0F);    
        }
        else if(strcmp((const char *)Rec_Buffer,"LED_OFF") == 0)
        {
            Led_State_Control(0X00);       
        }
        memset(Rec_Buffer,0,LEN);                           
        LEN =0;   
    }
}

void B2S(uint8 *Str)
{
	while(*Str!='\0')
	{
		if(*Str<='Z'&&*Str>='A')
			*Str += 32;
		Str++;
	}
}

#pragma import(__use_no_semihosting_swi) //ȡ��������״̬

struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;

int fputc(int ch, FILE *f) 
{
	while((USART1->SR & (0X01<<7)) == 0);
		USART1->DR=ch;
    return (ch);
}
int ferror(FILE *f) {
  /* Your implementation of ferror */
  return EOF;
}


void _ttywrch(int ch) {
  while((USART1->SR &(0X01<<7))==0);
		USART1->DR=ch;
}


void _sys_exit(int return_code) {
label:  goto label;  /* endless loop */
}



