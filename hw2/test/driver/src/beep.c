#include "beep.h"

void Beep_Io_Init(void)
{
	/*PF8���ó�ͨ���������*/
	RCC->AHB1ENR |= 0X01<<5; 		//����PF�˿�ʱ��
	GPIOF->MODER &=~ (0x03<<16);	//��0����
	GPIOF->MODER |= (0x01<<16);		//ͨ�����ģʽ
	GPIOF->OTYPER &=~ (0x01<<8);	//�������
	GPIOF->OSPEEDR &=~ (0X03<<16);	//����ٶ�Ϊ2MHz
	GPIOF->PUPDR &=~(0X03<<16);		//����ģʽ
	
	
}
void Beep_State_Contrl(u8 Beep_State)
{
	if(1==Beep_State)
		GPIOF->ODR |=(0X01<<8);			//����ߵ�ƽ��������	
	else
		GPIOF->ODR &=~(0X01<<8);		//����͵�ƽ��ƽ����������	
}

