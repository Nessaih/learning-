#include "motor.h"

void Motor_Init(void)
{	
	uint16 delay=0;
	//PB10�˿ڸ���
	RCC->AHB1ENR |=0X01<<1;
	GPIOB->MODER &=~ (0X03<<2);
	GPIOB->MODER |= (0X02<<20);
	GPIOB->PUPDR &=~ (0X03<<20);
	GPIOB->AFR[1] &=~ (0X0F<<8);
	GPIOB->AFR[1] |= (0X01<<8);
	//TIM2_CH3PWM���
	RCC->APB1ENR |= 0X01<<0;//timer2ʱ��ʹ��
	TIM2->CR1 |=0X01<<7;//TIM2_ARR �Ĵ������л���
	TIM2->CR1 &=~ ((0X01<<3)|(0X01<<2)|(0X01<<1));//�رյ�����ģʽ����������Դ��ʹ�ܸ���
	//TIM2->DIER |=(0X01<<3);//����CC3IE�ж�ʹ��;
	TIM2->DIER |=(0X01);//�����¼��ж�ʹ��;
	TIM2->CCMR2 &=~ (0X03<<0);//CC3ͨ������Ϊ���
	TIM2->CCMR2 &=~ (0X07<<4);//ch3�������/�Ƚ�ģʽ����
	TIM2->CCMR2 |=0X07<<4;//PWM ģʽ 2
	TIM2->CCMR2 |=0X01<<3;//����Ƚ� 3 Ԥװ��ʹ��

	
	TIM2->CCER &=~(0X01<<11);//CC2 ͨ������Ϊ����� CC2NP ���뱣������
	TIM2->CCER &=~(0X01<<9);//OCx�ߵ�ƽ��Ч(��OCx_REFD������˿ڲ�ȡ��)
	TIM2->CCER |=(0X01<<8);//CC3Eʹ�����
	
	TIM2->PSC = 100;//��Ƶ
	TIM2->ARR =1500;//����ֵ
	TIM2->CCR3 =1400 ;//�Ƚ�ֵ
	TIM2->EGR |=0X01;//���ɸ����¼�
	while(!((TIM2->SR)&0X01)&&delay<1680)//��ѯ��־,10us��ʱ�˳�
	{
		delay++;
	}
	TIM2->SR &=~ 0X01;//��������¼���־
	//TIM2->SR &=~ (0X01<<3);//���CC3IE�жϱ�־
	NVIC_SetPriorityGrouping(7-2); //����Ϊ��2��  
    NVIC_SetPriority(TIM2_IRQn,NVIC_EncodePriority(7-2,0,0));//�������ȼ�
	NVIC_EnableIRQ(TIM2_IRQn ); 
	TIM2->CR1 |=0X01;//������ʹ��
}
void TIM2_IRQHandler(void)
{
	/*static uint8 Timer2_Flag =1;
	if((TIM2->SR)&(0X01<<3))
	{
		//printf("TIME12�ж�");
		TIM2->SR &=~ (0X01<<3);//���CC2IE�жϱ�־
		if(TIM2->CCR3>1498)
		{
			 Timer2_Flag=0;
		}
		if(TIM2->CCR3<2)
		{
			 Timer2_Flag=1;
		}
		
		if(Timer2_Flag)
		{
			TIM2->CCR3 += 1;
		}
		else
		{
			TIM2->CCR3 -= 1;
		}
	}*/
	if((TIM2->SR)&(0X01<<0))
	{
		TIM2->SR &=~ (0X01<<0);	
	}
}
void Motor_Speed(uint8 speed_mode)
{
	switch(speed_mode)
	{
		case 0://�ر�
		{
			TIM2->CCER &=~ (0X01<<8);//CC3E��ֹ���
			TIM2->CR1 &=~ 0X01;//�������ر�
		}break;
		case 1://����
		{
			TIM2->CCR3 = 1150;
		}break;
		case 2://����
		{
			TIM2->CCR3 = 800;
		}break;
		case 3://����
		{
			TIM2->CCR3 = 300;
		}break;
		default:break;
	}
}
