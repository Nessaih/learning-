#include "led.h"



//PF   6  9  10   
//PC   0           �͵�ƽ��Ч

void led_init(void)
{
//��RCC����ʱ�Ӷ�Ӧλ
	RCC->AHB1ENR |= 1 << 2;
	RCC->AHB1ENR |= 1 << 5;
	
//����IO��ģʽ�Ĵ���
	GPIOF->MODER &= 0XFFC33FFF;
	GPIOF->MODER |= 0X00141000;
	GPIOC->MODER &= ~(3 << 0);
	GPIOC->MODER |= 1 << 0;
//�����������
	GPIOF->OTYPER &= 0XF9BF;
	GPIOC->OTYPER &= ~(1 << 0);
//��������ٶ�
	GPIOF->OSPEEDR &= 0XFFC33FFF;
	GPIOF->OSPEEDR |= 0X00141000;
	GPIOC->OSPEEDR &= ~(3 << 0);
	GPIOC->OSPEEDR |= (1 << 0);
//���ó�ʼ��״̬Ϊ�ߵ�ƽ
	GPIOF->ODR |= 0X0640;
	GPIOC->ODR |= 1 << 0;
}

void LED_ON(void)
{
	LED1_ON;
	LED2_ON;
	LED3_ON;
	LED4_ON;
}

void LED_OFF(void)
{
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
	LED4_OFF;
}


