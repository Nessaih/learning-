#include "key.h"
#include "includes.h"
void Key_Io_Init(void)
{
	//KEY1
	RCC->AHB1ENR |= 0X01;		//��PAʱ��
	GPIOA->MODER &=~ 0X03;		//��0��������λPA0ģʽ,����ģʽ
	GPIOA->PUPDR &=~0X03;		//PA0����ģʽ
	
	//KEY2,KEY3,KEY4
	RCC->AHB1ENR |= 0X01<<4;		//��PEʱ��
	GPIOE->MODER &=~ ((0X03<<4)|(0X03<<6)|(0X03<<8));//��0��������λPE234ģʽ,����ģʽ
	GPIOE->PUPDR &=~((0X03<<4)|(0X03<<6)|(0X03<<8));//PE234����ģʽ
}
	
uint8 Key_Scan(void)
{
	static uint8 Key_Sta = 1;//��������־
	if((KEY1_STATE||(!KEY2_STATE)||(!KEY3_STATE)||(!KEY4_STATE))&&Key_Sta)//��������Ϊ��
	{
		OSTimeDly(2);//10ms
		if(KEY1_STATE)
		{
			Key_Sta = 0;
			return 1;
		}
		if(!KEY2_STATE)
		{
			Key_Sta = 0;
			return 2;
		}
		if(!KEY3_STATE)
		{
			Key_Sta = 0;
			return 3;
		}
		if(!KEY4_STATE)
		{
			Key_Sta = 0;
			return 4;
		}
	}
	else if((!KEY1_STATE)&&KEY2_STATE&&KEY3_STATE&&KEY4_STATE)
	{
		Key_Sta = 1;
	}
	return 0;
		
}

