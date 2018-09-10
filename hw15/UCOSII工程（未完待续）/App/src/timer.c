#include "timer.h"
uint8 Timer12_Flag =1;
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
			{
				Usart1_Flag=1;
			}
		}
	}
}

/********************************************************************************************
*  �� �� ���� Time12_Configuration
*  ��    ��:  ������ʱ��Timer6ʹ���ж����ã��жϷ�ʽ��
*  ��������� (uint16 Psc,uint16 Arr) ��Ƶֵ������ֵ
*  ��������� ��
*  �� �� ֵ:  ��
*  ��    ��:  ��ΰ
*  �������:  2018-07-23--19:16
*  ע������:  ��Ƶֵ������ֵ����Ϊ16λ
********************************************************************************************/
void Time12_Configuration(uint16 Psc,uint16 Arr)
{
	uint16 delay=0;
	/*PB15��ʼ����ѡ���ù���TIM12_CH2*/
	RCC->AHB1ENR |= 0X01<<1; 
	GPIOB->MODER &= ~((uint32)0X03<<30);
    GPIOB->MODER |= (uint32)0X02<<30;//���ù���
    GPIOB->OTYPER &= ~(0X01<<15);//�������
	GPIOB->OSPEEDR &=~ ((uint32)0X03<<30);//����ٶȸ�λ
	GPIOB->OSPEEDR |=((uint32)0X02<<30);
    GPIOB->PUPDR &= ~((uint32)0X03<<30);//����
	GPIOB->AFR[1] &=~((uint32)0X0F<<28);
	GPIOB->AFR[1] |=((uint32)0X09<<28);//���ù���ѡ��
	
	/*TIM12����*/
	RCC->APB1ENR |= 0X01<<6;//timer12ʱ��ʹ��
	RCC->APB1RSTR |= (0X01<<6);//��λ��ʱ��
	RCC->APB1RSTR &=~ (0X01<<6);//ֹͣ��λ��ʱ��
	TIM12->CR1 |=0X01<<7;//TIM12_ARR �Ĵ������л���
	TIM12->CR1 &=~ ((0X01<<3)|(0X01<<2)|(0X01<<1));//�رյ�����ģʽ����������Դ��ʹ�ܸ���
	TIM12->DIER |=(0X01<<2)|(0X01) ;//����CC2IE�ж�ʹ��;�����ж�ʹ��
	
	
	TIM12->CCMR1 &=~ (0X03<<8);//CC2ͨ������Ϊ���
	TIM12->CCMR1 &=~ (0X07<<12);//ch2�������/�Ƚ�ģʽ����
	TIM12->CCMR1 |=0X07<<12;//PWM ģʽ 2
	TIM12->CCMR1 |=0X01<<11;//����Ƚ� 2 Ԥװ��ʹ��
	//TIM12->CCMR1 |=0X01<<10;//����Ƚ� 2 ����ʹ��
	
	TIM12->CCER &=~(0X01<<7);//CC2 ͨ������Ϊ����� CC2NP ���뱣������
	TIM12->CCER &=~(0X01<<5);//OC1 �ߵ�ƽ��Ч(��OC2_REFD������˿ڲ�ȡ��)
	TIM12->CCER |=(0X01<<4);//ch2ʹ�����
	
	TIM12->PSC = Psc-1;//��Ƶ
	TIM12->ARR =Arr-1;//����ֵ
	TIM12->CCR2 =10 ;//�Ƚ�ֵ
	
	TIM12->EGR |=0X01;//���ɸ����¼�
	while(!((TIM12->SR)&0X01)&&delay<1680)//��ѯ��־,10us��ʱ�˳�
	{
		delay++;
	}
	TIM12->SR &=~ 0X01;//��������¼���־
	TIM12->SR &=~ (0X01<<2);//���CC2IE�жϱ�־
	NVIC_SetPriorityGrouping(7-2); //����Ϊ��2��  
    NVIC_SetPriority(TIM8_BRK_TIM12_IRQn,NVIC_EncodePriority(7-2,0,0));//�������ȼ�
	NVIC_EnableIRQ(TIM8_BRK_TIM12_IRQn ); 

	TIM12->CR1 |=0X01;//������ʹ��
}

//�жϷ�����
void TIM8_BRK_TIM12_IRQHandler(void)
{
	if((TIM12->SR)&(0X01<<2))
	{
		//printf("TIME12�ж�");
		TIM12->SR &=~ (0X01<<2);//���CC2IE�жϱ�־
		if(TIM12->CCR2>1498)
		{
			 Timer12_Flag=0;
		}
		if(TIM12->CCR2<2)
		{
			 Timer12_Flag=1;
		}
		
		if(Timer12_Flag)
		{
			TIM12->CCR2=TIM12->CCR2+1;
		}
		else
		{
			TIM12->CCR2=TIM12->CCR2-1;
		}
	}
	if((TIM12->SR)&(0X01<<0))
	{
		TIM12->SR &=~ (0X01<<0);	
	}
}

/********************************************************************************************
*  �� �� ���� Time5_CH1_Capture_Configuration
*  ��    ��:  ������ʱ��Timer6ʹ���ж����ã��жϷ�ʽ��
*  ��������� (uint16 Psc,uint16 Arr) ��Ƶֵ������ֵ
*  ��������� ��
*  �� �� ֵ:  ��
*  ��    ��:  ��ΰ
*  �������:  2018-07-24--15:16
*  ע������:  ��Ƶֵ������ֵ����Ϊ16λ
********************************************************************************************/
void Time5_CH1_Capture_Configuration(uint16 Psc,uint16 Arr)
{
	uint16 delay=0;
	/*PA0��ʼ����ѡ���ù���TIM11_CH1*/
	RCC->AHB1ENR |= 0X01; //PAʱ��ʹ��
	GPIOA->MODER &= ~(0X03<<0);
    GPIOA->MODER |= 0X02<<0;//���ù���
    GPIOA->OTYPER &= ~(0X01<<0);//�������
	GPIOA->OSPEEDR &=~ (0X03<<0);//����ٶȸ�λ
	GPIOA->OSPEEDR |=(0X02<<0);
    GPIOA->PUPDR &= ~(0X03<<0);//����
	GPIOA->AFR[0] &=~(0X0F<<0);
	GPIOA->AFR[0] |=(0X02<<0);//PA0���ù���ѡ��TIM5_CH1
	
	/*TIM5����*/
	RCC->APB1ENR |= 0X01<<3;//timer5ʱ��ʹ��
	RCC->APB1RSTR |= (0X01<<3);//��λ��ʱ��
	RCC->APB1RSTR &=~ (0X01<<3);//ֹͣ��λ��ʱ��
	
	TIM5->CR1 &=~ (0X03<<8);//CKD����Ƶ
	TIM5->CR1 |=0X01<<7;//TIM5_ARR �Ĵ������л���
	TIM5->CR1 &=~ ((0X03<<5)|(0X01<<4)|(0X01<<3)|(0X01<<2)|(0X01<<1));//���ض���ģʽ��������ģʽ���رյ�����ģʽ����������Դ��ʹ�ܸ���
	TIM5->DIER |=(0X01<<1)|(0X01) ;//����CC1IE�ж�ʹ��;�����¼��ж�ʹ��
	TIM5->CCMR1 &=~ (0X03<<0);
	TIM5->CCMR1 |=0X01<<0;// CC1 ͨ������Ϊ���룬IC1ӳ�䵽 TI1�ϡ�
	TIM5->CCMR1 &=~(0X03<<2);//���벶�񲻷�Ƶ
	TIM5->CCMR1 &=~(0X0F<<4);//���˲���	
	TIM5->CCER &=~(0X01<<3);
	TIM5->CCER &=~(0X01<<1);//�����ش�������00
	TIM5->CCER |=(0X01<<0);//����ʹ��
	
	TIM5->PSC = Psc-1;//��Ƶ
	TIM5->ARR =Arr-1;//����ֵ
	
	TIM5->EGR |=0X01;//���ɸ����¼�
	while(!((TIM5->SR)&0X01)&&delay<1680)//��ѯ��־,10us��ʱ�˳�
	{
		delay++;
	}
	TIM5->SR &=~ 0X01;//��������¼���־
	TIM5->SR &=~ (0X01<<1);//���CC2IE�жϱ�־
	NVIC_SetPriorityGrouping(7-2); //����Ϊ��2��  
    NVIC_SetPriority(TIM5_IRQn,NVIC_EncodePriority(7-2,0,0));//�������ȼ�
	NVIC_EnableIRQ(TIM5_IRQn ); 

	TIM5->CR1 |=0X01;//������ʹ��
}

//�жϷ�����
uint8 Capture_Start_Flag = 0,Capture_End_Flag;
uint32 Overflow_Count=0;//�����¼�����
uint16 Capture_Up_Count,Capture_Down_Count;
uint32 Capture_Sum_Count;
void TIM5_IRQHandler(void)
{
	if((TIM5->SR)&(0X01<<0))
	{
		TIM5->SR &=~ (0X01<<0);	//��������¼�
		if(Capture_Start_Flag==1)
		{
			Overflow_Count++;
		}
	}
	
	if((TIM5->SR)&(0X01<<1))
	{
		TIM5->SR &=~ (0X01<<1);	//��������־
		if(Capture_Start_Flag == 0)
		{
			Capture_Up_Count = TIM5->CCR1;
			TIM5->CCER |=0X01<<1;//�л�Ϊ�½��ز���
			Capture_Start_Flag = 1;
		}
		else
		{
			Capture_Down_Count = TIM5->CCR1;
			Capture_Sum_Count = Overflow_Count * Capture_ARR - Capture_Up_Count + Capture_Down_Count;
			TIM5->CCER &=~(0X01<<1);//�л�Ϊ�����ز���
			Overflow_Count = 0;
			Capture_Start_Flag = 0;
			Capture_End_Flag =1;
		}
	}
}

