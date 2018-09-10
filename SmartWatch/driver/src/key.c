#include "key.h"
#include "delay.h"

uint8 Key_Value = 0;
static u8 KeyStatus[5] = {0, 0, 0,  0,  0}; //����5��������ʵʱ״̬
						//L  R  Dn  Up  Ok


//ʱ��Դ 100Mhz
void TIM3_Init()
{
	RCC->APB1ENR |= 1<<1;//TIM3ʱ��ʹ��
	TIM3->PSC = 100-1;		//100��Ƶ  ������ʱ�ӣ�1MHZ
	TIM3->ARR = 5000-1;     // ��ʱ 5MS

	/* TIM3_TRGO ---> ADC1 */
	TIM3->CR2 &= ~(7<<4);
	TIM3->CR2 |= (2<<4);	//ѡ������¼���Ϊ TRGO	


	TIM3->CR1 |= 1;		//������ʹ��
	TIM3->DIER |= 1;		//�����ж�ʹ��
	NVIC_EnableIRQ(TIM3_IRQn);//NVIC ��Ӧ���ж�ͨ��ʹ��
}
//��ʱ 5MS ���һ�ΰ���
void TIM3_IRQHandler()
{
	static u8 key_buf = 0;
	
	if (TIM3->SR & 1)
	{
		TIM3->SR &= ~1;
		
		key_buf <<= 1;
		key_buf |= KEY_OK_IO;//��ȡOK����״̬
		
		if (key_buf == 0)	   //�ȶ��ɿ�
		{
			KeyStatus[4] = 0;
		}
		else if (key_buf == 0xff)//�ȶ�����
		{
			KeyStatus[4] = 1;
		}
	}
}


//����ADC1_CH3�ɼ������ӿ�
static void ADC1_InitCh3()
{
	/* ����ADC���� ������ת�� */
	RCC->AHB1ENR |= 1;
	RCC->APB2ENR |= 1<<8;//ADC1
	
	GPIOA->MODER |= 3<<6;//PA3  ģ��ģʽ
	
	ADC->CCR |= 3<<16;  // 50/8 Mhz
	
	ADC1->SQR1 &= ~(0XF<<20);//1��ͨ���ڹ�����ת��
	ADC1->SQR3 &= ~(0X1F<<0);
	ADC1->SQR3 |= (0X3<<0);  //ͨ��3 ��һ��ת��
	
	ADC1->SMPR2 |= 4<<9;		//ͨ��3������������
	
	ADC1->CR2 &= ~(3<<28);
	ADC1->CR2 |= (1<<28);		//ʹ���ⲿ����
	
	ADC1->CR2 &= ~(0XF<<24);
	ADC1->CR2 |= (0X8<<24);	//ѡ�� TIM3 TRGO��Ϊ����Դ
	
	ADC1->CR1 |= 1<<5;        //ʹ��ADC EOC�ж�
	NVIC_EnableIRQ(ADC_IRQn);//ʹ���ں˶�Ӧ���ж�ͨ��
	
	ADC1->CR2 |= 1;//ʹ��ADC1
}


void Key_Init()
{
	RCC->AHB1ENR |= 1<<0; //ʹ��PAʱ��

	/* ��ʼ��PA0 */
	GPIOA->MODER &= ~(3);//����ģʽ   
	GPIOA->PUPDR &= ~(3);
	
	ADC1_InitCh3();
	TIM3_Init();   //5ms
}



void ADC_IRQHandler()//��ʱ��3��ÿ���5ms����һ��ADת��
{
	u8 i;       
	u16 AdcValue;
	static u8 AdcKeyBuf[4] = {0,  0,  0,  0};
	                       //   L   R   Dn  Up
	AdcValue = ADC1->DR;
	
	AdcKeyBuf[0] <<= 1;
	AdcKeyBuf[1] <<= 1;
	AdcKeyBuf[2] <<= 1;
	AdcKeyBuf[3] <<= 1;
	
	if (AdcValue > 3723)                          // 3v���� (3.3V)
	{
		AdcKeyBuf[0] |= 1;	 //��⵽LEFT ����
	}	
	else if (AdcValue >1737 && AdcValue < 2234) //1.4v ~ 1.8v (1.65V)
	{
		AdcKeyBuf[1] |= 1;	 //��⵽RIGHT ����
	}
	else if (AdcValue >1241 && AdcValue < 1613) //1.0v ~ 1.3v (1.10V)
	{
		AdcKeyBuf[2] |= 1;	 //��⵽DOWN ����
	}
	else if (AdcValue >744 && AdcValue < 1179)  //0.6v ~ 0.95v(0.825V)
	{
		AdcKeyBuf[3] |= 1;	 //��⵽UP ����
	}
	for (i=0; i<4; i++)
	{
		if (AdcKeyBuf[i] == 0xff) //�ȶ�����
		{
			KeyStatus[i] = 1;
		}
		else if (AdcKeyBuf[i] == 0x00)//�ȶ��ɿ�
		{
			KeyStatus[i] = 0;
		}
	}
	
}
//������·���1�� �Ҽ�����2���¼�����3���ϼ�����4��ok������5
//û�а�������������0.
uint8_t Key_Scan()
{
	u8 i;
	static u8 KeyLastSta[5]={0,0,0,0,0};
	
	for (i=0; i<5; i++)
	{
		if (KeyLastSta[i] != KeyStatus[i])
		{
			KeyLastSta[i] = KeyStatus[i];
			
			if (KeyStatus[i] == 1)
			{
				return  i+1;//������Ч
			}
		}
	}
	return 0;
}
