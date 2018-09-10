#include "adc.h"
#include "usart1.h"
void ADC1_Configuration(void)
{
	RCC->AHB1ENR |=0X01;
	RCC->APB2ENR |=0X01<<8;//ADC1ʱ��ʹ��
	GPIOA->MODER |=0X03<<10;//PA5ģ��
	ADC1->CR1 &=~ ((0X03<<24)|(0X01<<8));//�ֱ���12λ����ֹɨ��
	ADC1->CR2 &=~ ((0X01<<11)|(0X01<<1));//�Ҷ��룬����ת��ģʽ
	ADC1->CR2 |= (0X01<<10);//EOCS
	ADC1->SMPR2 &=~(0X07<<0);//ͨ��0����ʱ��3������
	ADC1->SQR1 &=~ (0X0F<<20);//�������г���1
	ADC1->SQR3 |=0X05;//IN5�������е�һ
	ADC->CCR &=~ (0X03<<16);
	ADC->CCR |= (0X03<<16);//4��Ƶ
	ADC1->CR2 |= (0X01<<0);//ADCʹ��
}

void ADC1_Sampling(void)
{
	static uint16 Old_Value=0;
	uint16 Digital_Value,Analog_Value;
	ADC1->CR2 |= 0X01<<30;
	while(!(ADC1->SR&0X02));
	
	Digital_Value = ADC1->DR;
	Analog_Value=3300.0/4096*Digital_Value;

	if((Analog_Value / 100) != Old_Value)
    {
       Old_Value = Analog_Value / 100;
       printf("%f\r\n", (float)Analog_Value / 1000);
    }
}
