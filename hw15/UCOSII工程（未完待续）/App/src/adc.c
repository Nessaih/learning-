#include "adc.h"
#include "usart1.h"

/********************************************************************************************
*  �� �� ���� ADC1_Configuration
*  ��    ��:  ADC1��ʼ������(�жϷ�ʽ)
*  ��������� ��   
*  ��������� ��
*  �� �� ֵ:  ��
*  ��    ��:  ��ΰ
*  �������:  2018-07-25
*  ע������:  ��
********************************************************************************************/
void ADC1_Configuration(void)
{
	RCC->AHB1ENR |=0X01;
	RCC->APB2ENR |=0X01<<8;//ADC1ʱ��ʹ��
	GPIOA->MODER |=0X03<<10;//PA5ģ��
	ADC1->CR1 &=~ ((0X03<<24)|(0X01<<8));//�ֱ���12λ����ֹɨ��
	ADC1->CR1 |= 0X01<<5;//EOCIE�ж�ʹ��
	ADC1->CR2 &=~ (0X01<<11);//�Ҷ���
	ADC1->CR2 |= (0X01<<1);//����ת��ģʽ
	ADC1->CR2 |= (0X01<<10);//EOCS
	ADC1->SMPR1 &=~(0X07<<18);
	ADC1->SMPR1 |= (0X03<<18);//ͨ��16����ʱ��56������
	ADC1->SQR1 &=~ (0X0F<<20);//�������г���1
	ADC1->SQR3 |=0X10;//IN16�������е�һ
	ADC->CCR |= (0X01<<23);//���¶ȴ������ӵ���ģʽ�л���
	ADC->CCR &=~ (0X03<<16);
	ADC->CCR |= (0X03<<16);//4��Ƶ:21MHz
	ADC1->SR &=~ (0X01<<1);//���ECO��־
	NVIC_SetPriorityGrouping(7-2); //����Ϊ��2��  
    NVIC_SetPriority(ADC_IRQn,NVIC_EncodePriority(7-2,1,0));//�������ȼ�
	NVIC_EnableIRQ(ADC_IRQn); 
	ADC1->CR2 |= (0X01<<0);//ADCʹ��
	ADC1->CR2 |= 0X01<<30;//�������ת��
}
uint16 Old_Value=0;
uint16 Digital_Value,Analog_Value;
//�жϺ���
void ADC_IRQHandler(void)
{
	if(ADC1->SR&(0X01<<1))
	{
		ADC1->SR &=~ (0X01<<1);//���ECO��־
		{
			Digital_Value = ADC1->DR;
			Analog_Value=3300.0/4096*Digital_Value;
		}
	}
}
	
void ADC1_Temperature_Calculation(void)
{
	float Chip_Temperature;
	if((Analog_Value / 300) != Old_Value)
    {
		Old_Value = Analog_Value / 300;
		/*Analog_Value������1000�������ݣ�ԭʼ��ʽΪ��
		Chip_Temperature = ((Analog_Value/1000 - 0.76)/2.5)+25;*/
		Chip_Temperature = ((Analog_Value - 760)/2.5)+25;//2500����.0�����ʽ���Զ�ת�����ͼ��㣬���С������
		printf("%.2f\r\n", Chip_Temperature);
    }
}
