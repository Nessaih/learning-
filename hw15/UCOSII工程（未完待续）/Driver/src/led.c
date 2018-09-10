#include "led.h"

/********************************************************************************************
*  �� �� ���� Led_Io_Init
*  ��    ��:  LED�˿ڳ�ʼ��
*  ��������� ��   
*  ��������� ��
*  �� �� ֵ:  ��
*  ��    ��:  �±�
*  �������:  2018-07-18
*  ע������:  ��
********************************************************************************************/
void Led_Io_Init(void)
{
    /*PF6,PF9,PF10 ���ó�ͨ���������ģʽ*/
    RCC->AHB1ENR |= (0X01<<2)|(0X01<<5);        //����PC.PF�˿�ʱ��
 
    GPIOF->MODER &= ~((0X03<<12)|(0X03<<18)|(0X03<<20));    //�������
    GPIOF->MODER |= (0X01<<12)|(0X01<<18)|(0X01<<20);       //ͨ�����ģʽ
    GPIOF->OTYPER &= ~((0X01<<6)|(0X01<<9)|(0X01<<10));     //����ģʽ
    GPIOF->OSPEEDR &= ~((0X03<<12)|(0X03<<18)|(0X03<<20));  //����ٶ�Ϊ2MHZ
    GPIOF->PUPDR &=  ~((0X03<<12)|(0X03<<18)|(0X03<<20));    //����ģʽ
    //GPIOF->ODR &= ~((0X01<<6)|(0X01<<9)|(0X01<<10));       //����͵�ƽ����  
    
    GPIOC->MODER &= ~(0X03<<0);
    GPIOC->MODER |= 0X01<<0;
    GPIOC->OTYPER &= ~(0X01<<0);
    GPIOC->OSPEEDR &= ~(0X03<<0);
    GPIOC->PUPDR &= ~(0X03<<0);
    //GPIOC->ODR &= ~(0X01<<0); //����͵�ƽ����  
	Led_State_Control(0X03);
}
/********************************************************************************************
*  �� �� ���� Led_State_Control
*  ��    ��:  LED��״̬����
*  ��������� u8 Led_State ��D0~D3����LED1��LED2��LED3��LED4������,1Ϊ������0Ϊ�ر�
							D4~D7����LED1��LED2��LED3��LED4�ķ�ת,1Ϊ��ת��0Ϊ����
*  ��������� ��
*  �� �� ֵ:  ��
*  ��    ��:  ��ΰ
*  �������:  2018-07-22
*  ע������:  ��λ�͸�λ����ͬʱ����,��λΪ0ʱ���Ƶ�λ����λ��Ϊ0ʱ���Ƶ�λ
********************************************************************************************/
void Led_State_Control(u8 Led_State)
{
	if(!(Led_State&0XF0))//��λ����״̬
	{
		//LED1����
		if(Led_State&0x01)
		{
			LED1_STATE = 0;
		}
		else
		{
			LED1_STATE = 1;
		}
		
		//LED2����
		if(Led_State&0x02)
		{
			LED2_STATE = 0;//��
		}
		else
		{
			LED2_STATE = 1;//��
		}
		
		//LED3����
		if(Led_State&0x04)
		{
			LED3_STATE = 0;
		}
		else
		{
			LED3_STATE = 1;
		}
		
		//LED4����
		if(Led_State&0x08)
		{
			LED4_STATE = 0;
		}
		else
		{
			LED4_STATE = 1;
		}
	}
	else//��λ���Ʒ�ת
	{
		//LED1����
		if(Led_State&0x10)
		{
			LED1_STATE =! LED1_STATE;
		}
		//LED2����
		if(Led_State&0x20)
		{
			LED2_STATE =! LED2_STATE;
		}
		//LED3����
		if(Led_State&0x40)
		{
			LED3_STATE =! LED3_STATE;
		}
		//LED4����
		if(Led_State&0x80)
		{
			LED4_STATE =! LED4_STATE;
		}
	}
	
	
	
}
void Led_Delay(uint32 i) //��ʱ i*100 us
{
	uint32 j;
	for(;i>0;i--)
		for(j=0;j<=16800;j++);
}
void Water_Light(void)
{
	if(Led_Speed!=0XFFFF)
	{
		Led_State_Control(0X01);
		Led_Delay(Led_Speed);
		Led_State_Control(0X02);
		Led_Delay(Led_Speed);
		Led_State_Control(0X04);
		Led_Delay(Led_Speed);
		Led_State_Control(0X08);
		Led_Delay(Led_Speed);
	}
}
void Water_Light_Control(uint8 Up_down)
{
	if(Led_Speed>0||Led_Speed<500)
	{
		if(Up_down)
			Led_Speed -= 20;
		else
			Led_Speed += 20;
	}
}
void Water_Light_Pause(void)
{
	if(Led_Speed!=0XFFFF)
		Led_Speed_Recording=Led_Speed;
	Led_Speed=0XFFFF;
}
void Water_Light_Keepon(void)
{
	Led_Speed=Led_Speed_Recording;
}
