#include "usart1.h"

void Usart1_Init(void)
{
	
	//�����ʷ�Ƶ�������
	float USART1DIV;
	uint16 DIV_Man,DIV_Frac;
	
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
	USART1DIV = FCK / (8*(2-((USART1->CR1&0X01<<15)>>15))*BAUD_RATE);
	DIV_Man = ((uint16)USART1DIV)<<4 ;
	DIV_Frac = (uint16)((USART1DIV-DIV_Man/16)*16 + 0.5);//+0.5��ʾ��������
	USART1->BRR = DIV_Man | DIV_Frac;
	
	//USART1->BRR = 0X222<<4 | 0X0E;		//�������ֶ�����9600
	
	USART1->CR1 |= 0X01<<13;		//USART1ʹ��
}

void Usart1_Send(uint8 Msg)
{
	uint32 delay = 0;
	while(!(USART1->SR&(0X01<<7))&&(delay<168000))//TXE=0��һ������û����,�ȴ�1us
	{
		delay++;
	}
	if(USART1->SR&(0X01<<7))//TXE=1��ʾ��һ�����ݴ���
		USART1->DR = Msg;

}

void Usart1_Str_Send(uint8 Str[])
{
	uint16 i; 
	for(i=0;Str[i]!='\0';i++)
	{
		Usart1_Send(Str[i]);
	}
}

uint8 Usart1_Receive(void)
{
	uint8 Msg='\0';
	uint32 delay = 0;
	while(!(USART1->SR&(0X01<<5))&&(delay<168000))//RXNE=0��������δ���,�ȴ�1us
	{
		delay++;
	}
	if(USART1->SR&(0X01<<5))//RXNE=1 �������
		Msg=USART1->DR ;
	return Msg;

}
void Usart1_Str_Receive(uint8 Str[])
{
	uint8 Msg,i=0;
	do{
		Msg = Usart1_Receive();
		Str[i] = Msg;
	}while(Msg!='\0');
}	

