#include "EXTI.h"
/********************************************************************************************
*  �� �� ���� EXTI_Configration
*  ��    ��:  PA0�ⲿ�ж�����
*  ��������� ��   
*  ��������� ��
*  �� �� ֵ:  ��
*  ��    ��:  ��ΰ
*  �������:  2018-07-21
*  ע������:  ��
********************************************************************************************/
void EXTI_Configration(void)
{
	//IO
	RCC->AHB1ENR |= (0X01|0X01<<4);	//PA,PEʱ�ӿ���
	GPIOA->MODER &=~ 0X03;			//PA0����
	GPIOA->PUPDR &=~ 0X03;			//PA0����ģʽ
	GPIOE->MODER &=~ ((0X03<<4)|(0X03<<6)|(0X03<<8));			//PE2,3,4����
	GPIOE->PUPDR &=~ ((0X03<<4)|(0X03<<6)|(0X03<<8));			//PE2,3,4����ģʽ
	
	//EXTI
	RCC->APB2ENR |= 0X01<<14;		//ϵͳ����ʱ�ӿ��� 
	SYSCFG->EXTICR[0] &=~(0X0F|(0X0F<<8)|(0X0F<<12));//�ⲿ�ж�ѡ��EXTI0ѡ��PA0,
	SYSCFG->EXTICR[0] |=((0X04<<8)|(0X04<<12));//�ⲿ�ж�ѡ��EXTI2ѡ��PE2,EXTI3ѡ��PE3
	SYSCFG->EXTICR[1] &=~(0X04<<0);		
	SYSCFG->EXTICR[1] |= (0X04<<0);//�ⲿ�ж�ѡ��EXTI4ѡ��PE4
	
	EXTI->IMR |= (0X01|(0X01<<2)|(0X01<<3)|(0X01<<4));			//EXTI0,2,3,4 �жϲ�����
	EXTI->EMR &=~ (0X01|(0X01<<2)|(0X01<<3)|(0X01<<4));			//EXTI0,2,3,4 �¼�����
	EXTI->RTSR |= (0X01|(0X01<<2)|(0X01<<3)|(0X01<<4));			//�����ش���
	//EXTI->FTSR |= (0X01|(0X01<<2)|(0X01<<3)|(0X01<<4));			//�½��ش���
	EXTI->SWIER &=~ (0X01|(0X01<<2)|(0X01<<3)|(0X01<<4));		//����жϲ�����
	EXTI->PR |= (0X01|(0X01<<2)|(0X01<<3)|(0X01<<4));			//д1����жϹ����־λ
	
	//�жϷ���ѡ��ڶ���
	NVIC_SetPriorityGrouping(7-2);
	//���ȼ����ã���ռ0����Ӧ0
	NVIC_SetPriority(EXTI0_IRQn,NVIC_EncodePriority(7-2,0,0));
	NVIC_SetPriority(EXTI2_IRQn,NVIC_EncodePriority(7-2,0,0));
	NVIC_SetPriority(EXTI3_IRQn,NVIC_EncodePriority(7-2,0,0));
	NVIC_SetPriority(EXTI4_IRQn,NVIC_EncodePriority(7-2,0,0));
	//�ж�ʹ��
	NVIC_EnableIRQ(EXTI0_IRQn);									
	NVIC_EnableIRQ(EXTI2_IRQn);
	NVIC_EnableIRQ(EXTI3_IRQn);
	NVIC_EnableIRQ(EXTI4_IRQn);

}

void EXTI0_IRQHandler(void)
{
	if(EXTI->PR & (0X01<<0))
    {
        EXTI->PR |= 0X01<<0;  //�������λ
       // printf("EXTI->IRQ\r\n");
        LED1_STATE = !LED1_STATE;
    }
}
void EXTI2_IRQHandler(void)
{
	if(EXTI->PR & (0X01<<2))
    {
        EXTI->PR |= 0X01<<2;  //�������λ
       // printf("EXTI->IRQ\r\n");
        LED2_STATE = !LED2_STATE;
    }
}
void EXTI3_IRQHandler(void)
{
	if(EXTI->PR & (0X01<<3))
    {
        EXTI->PR |= 0X01<<3;  //�������λ
       // printf("EXTI->IRQ\r\n");
        LED3_STATE = !LED3_STATE;
    }
}
void EXTI4_IRQHandler(void)
{
	if(EXTI->PR & (0X01<<4))
    {
        EXTI->PR |= 0X01<<4;  //�������λ
       // printf("EXTI->IRQ\r\n");
        LED4_STATE = !LED4_STATE;
    }
}
