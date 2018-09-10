#include "usart.h"
#include "menu.h"
#include "key.h"
uint8 Buffer[MAX_LEN];
uint8 Receive_Flag=0,Time_Out=3;
uint16 LEN=0;
uint8 Bluetooth_Control_Flag = 0;
/********************************************************************************************
*  �� �� ���� Time9_Configuration
*  ��    ��:  ������ʱ��Timer6ʹ���ж����ã��жϷ�ʽ��
*  ��������� (uint16 Psc,uint16 Arr) ��Ƶֵ������ֵ,
			  ����(0,0)��Ĭ������Ϊ(10000,100)
*  ��������� ��
*  �� �� ֵ:  ��
*  ��    ��:  ��ΰ
*  �������:  2018-08-9
*  ע������:  ʱ��Դ��100MHz����Ƶֵ������ֵ����Ϊ16λ
********************************************************************************************/
void Time9_Configuration(uint16 Psc,uint16 Arr)
{	
	uint16 delay=0;
	if(Psc==0&&Arr==0)
	{
		Psc = 10000;
		Arr = 100; 
		
	}
	RCC->APB2ENR |=0X01<<16;//��ʱ��ʱ��ʹ��
	RCC->APB2RSTR |= (0X01<<16);//��λ��ʱ��
	RCC->APB2RSTR &=~ (0X01<<16);//ֹͣ��λ��ʱ��
	TIM9->CR1 |=0X01<<7;	//ʹ��Ӱ�ӼĴ���
	TIM9->CR1  &=~ (0X01<<2);//��������Դ
	TIM9->CR1  &=~ (0X01<<1);//ʹ�ܸ���
	TIM9->DIER |= 0X01;//�����¼��ж�ʹ��(�����жϣ�������ʱ����)
	TIM9->PSC = Psc-1;//ʱ�ӷ�Ƶ
	TIM9->ARR = Arr-1;//����ֵ
	TIM9->CNT = 0X00;//��0������
	TIM9->EGR |= 0X01;//���ɸ����¼�
	while(!((TIM9->SR)&0X01)&&delay<1000)//��ѯ��־,10us��ʱ�˳�
	{
		delay++;
	}
	if(delay>=1000)
		printf("\nTIM9��־λ��ʱ\n");
	TIM9->SR &=~ 0X01;//�����־
	NVIC_SetPriorityGrouping(7-2); //����Ϊ��2��  
    NVIC_SetPriority(TIM1_BRK_TIM9_IRQn ,NVIC_EncodePriority(7-2,0,0));//�������ȼ�
	NVIC_EnableIRQ(TIM1_BRK_TIM9_IRQn); 
	
	TIM9->CR1 |=0X01<<0;//������ʹ��
}
//�жϷ�����
void TIM1_BRK_TIM9_IRQHandler()
{
	if(TIM9->SR&0X01)
	{
		TIM9->SR &=~ 0X01;//�����־
		//LED1_OFF;
		
		/*usart1��ʱ����*/
		if(Time_Out)
		{
			if(--Time_Out==0)
			{
				Receive_Flag=1;
			}
			
		}
	}
}
/********************************************************************************************
*  �� �� ���� Usart1_Init
*  ��    ��:  Usart1���ڳ�ʼ��
*  ��������� ��   
*  ��������� ��
*  �� �� ֵ:  ��
*  ��    ��:  ��ΰ
*  �������:  2018-08-9
*  ע������:  ��
********************************************************************************************/
void Usart1_Init(void)
{
	
	//�����ʷ�Ƶ�������
	double USART1DIV;
	uint16 DIV_Man,DIV_Frac,OVER8;
	
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
	OVER8 = (USART1->CR1&0X01<<15)>>15;
	USART1DIV = FCK / (8*(2-OVER8)*BAUD_RATE);
	DIV_Man = (uint16)USART1DIV;
	DIV_Frac = (uint16)((USART1DIV-DIV_Man)*16 + 0.5);//+0.5��ʾ��������
	if(DIV_Frac>15)
	{
		DIV_Man++ ; 
		DIV_Frac -= 16;
	}
	USART1->BRR = (DIV_Man<<4)| DIV_Frac;

	
	USART1->CR1 |= (0X01<<5);//�����ж�ʹ�ܣ������ж�ʹ��
	USART1->SR &=~ (0X01<<5);//�жϱ�־λ���
	NVIC_SetPriorityGrouping(7-2); //����Ϊ��2��  
    NVIC_SetPriority(USART1_IRQn,NVIC_EncodePriority(7-2,0,0));//�������ȼ�
	NVIC_EnableIRQ(USART1_IRQn); 
	USART1->CR1 |= 0X01<<13;		//USART1ʹ��
	Time9_Configuration(0,0);
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


//void USART1_IRQHandler(void)
//{
//	uint8 Receive_Data;
//    if(USART1->SR & (0X01<<5))
//    {
//		Time_Out = 3;//˼����Time_Out = 3;���� if(Receive_Flag == 0)�����������ʲô����
//		Receive_Data = USART1->DR;
//        if(Receive_Flag == 0)
//        {
//            Buffer[LEN++] = Receive_Data;
//        }
//    }
//}
void USART1_IRQHandler(void)
{
	uint8 Receive_Data,i;
    if(USART1->SR & (0X01<<5))
    {
		Receive_Data = USART1->DR;
		Buffer[LEN++] = Receive_Data;
		if(Buffer[0]==0xd0&&Buffer[1]==0x01)
		{//�����ʲ���
			Bluetooth_Control_Flag = 1;
		}
		else if(Buffer[0]==0xd0&&Buffer[1]==00)
		{//�ر����ʲ���
			Bluetooth_Control_Flag = 2;
		}
		else if(Buffer[0]==0x90&&Buffer[1]==0x01)
		{
			Bluetooth_Control_Flag = 3;
		}
		else if(Buffer[0]==0x90&&Buffer[1]==0x00)
		{
			Bluetooth_Control_Flag = 4;
		}
		if(LEN>=18)
		{
			LEN = 0;
			memset(Buffer,0,18);
		}
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
void Led_Switch(void)
{
    if(Receive_Flag)
    {
        Receive_Flag = 0;
        Str_Send(Buffer); 
		Byte_Send('\n');
        if(strcmp((const char *)Buffer,"LED_ON") == 0)
        {
			LED1_ON;    
        }
        else if(strcmp((const char *)Buffer,"LED_OFF") == 0)
        {
            LED1_OFF;       
        }
        memset(Buffer,0,LEN);                           
        LEN =0;   
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

