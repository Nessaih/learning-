#include "timer.h"

/********************************************************************************************
*  �� �� ���� Time6_Configuration
*  ��    ��:  ������ʱ��Timer6ʹ���ж����ã��жϷ�ʽ��
*  ��������� (uint16 Psc,uint16 Arr) ��Ƶֵ������ֵ
*  ��������� ��
*  �� �� ֵ:  ��
*  ��    ��:  ��ΰ
*  �������:  2018-07-23
*  ע������:  ��Ƶֵ������ֵ����Ϊ16λ
********************************************************************************************/
void Time6_Configuration(uint16 Psc,uint16 Arr)
{	
	uint16 delay=0;
	RCC->APB1ENR |=0X01<<4;//��ʱ��ʱ��ʹ��
	RCC->APB1RSTR |= (0X01<<4);//��λ��ʱ��
	RCC->APB1RSTR &=~ (0X01<<4);//ֹͣ��λ��ʱ��
	TIM6->CR1 |=0X01<<7;	//ʹ��Ӱ�ӼĴ���
	TIM6->CR1 &=~ (0X01<<3);//�رյ�����ģʽ
	TIM6->CR1  &=~ (0X01<<2);//��������Դ
	TIM6->CR1  &=~ (0X01<<1);//ʹ�ܸ���
	TIM6->DIER |= 0X01;//�ж�ʹ��
	TIM6->PSC = Psc;//ʱ�ӷ�Ƶ
	TIM6->ARR = Arr;//����ֵ
	TIM6->CNT = 0X00;//��0������
	TIM6->EGR |= 0X01;//���ɸ����¼�
	while(!((TIM6->SR)&0X01)&&delay<1680)//��ѯ��־,10us��ʱ�˳�
	{
		delay++;
	}
	TIM6->SR &=~ 0X01;//�����־
	
	NVIC_SetPriorityGrouping(7-2); //����Ϊ��2��  
    NVIC_SetPriority(TIM6_DAC_IRQn ,NVIC_EncodePriority(7-2,0,0));//�������ȼ�
	NVIC_EnableIRQ(TIM6_DAC_IRQn); 
	
	TIM6->CR1 |=0X01<<0;//������ʹ��
}

//�жϷ�����
void TIM6_DAC_IRQHandler()
{
	if((TIM6->SR)&0X01)
	{
		TIM6->SR &=~ 0X01;//�����־
		
		
		/*usart1��ʱ����*/
		if(Time_Out)
		{
			if(--Time_Out==0)
				Flag=1;
		}
	}
}
