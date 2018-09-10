#include "rtc.h"

	char Week[15]={0XD2,0XBB,
					0XB6,0XFE,
					0XC8,0XFD,
					0XCB,0XC4,
					0XCE,0XE5,
					0XC1,0XF9,
					0XC8,0XD5,0
					};
void RTC_Init(void)
{
	uint16 delay = 10;
	RCC->APB1ENR |=0X01<<28;//��Դ�ӿ�ʱ��ʹ��
	PWR->CR |= 0X01<<8;//ʹ�ܱ�����д����
	RCC->BDCR |= 0X01;//LSEONʹ��
	do
	{
		delay_ms(1);
		delay--;
	}while(delay&&(!(RCC->BDCR&0X01)));//�ж�LSE�Ƿ��������ʱ�˳�
	if(!(RCC->BDCR&0X01))//���LSEδ����������LSIʱ��
	{
//		�ж�LSI�Ƿ����������������
//		RCC->BDCR &=~ (0X03<<8);
//		RCC->BDCR |= 0X10;
	}
	else//���LSE������ѡ��LSEΪRTCʱ��Դ
	{
		RCC->BDCR &=~ (0X03<<8);
		RCC->BDCR |= 0X01<<8;//ѡ��LSEΪRTCʱ��Դ
		RCC->BDCR |= 0X01<<15;//RTCʹ��
	}

	RTC->WPR =0XCA;
	RTC->WPR =0X53;//����д����
}
uint8 BCD_encode(uint8 num,uint8 flag)
{
	uint8 temp=0;
	if(flag)//flagΪ�棺����0x18-->18
	{
		temp = ((num>>4)&0X0F)*10 +(num&0X0F);
	} 
	else//flagΪ0������18-->0x18
	{
		temp = ((num/10)<<4)|(num%10);
	}
	return temp;
}
void RTC_Setting(void)//��������ʱ������
{
	uint16 delay = 10;
	uint32 temp = 0;
	
	RTC_Date dt ={18,7,27,5,9,8,30,0};//2018-7-27--17:11:30
	PRTC_Date rtc_dt = &dt;
	
	RTC->WPR =0XCA;
	RTC->WPR =0X53;//����д����
	RTC->ISR |= 0X01<<7;//��ʼRTC��ʼ������
	do
	{
		delay_ms(1);
		delay--;
	}while(delay&&(!(RTC->ISR&(0X01<<6))));//�ж��Ƿ��ܳ�ʼ������ʱ�˳�
	RTC->CR &=~ ((0X01<<6)|(0X01<<5));//����24Сʱ��ʽ,����Ӱ�ӼĴ���
	RTC->PRER = 255;//����������ͬ����Ƶ����λ��
	RTC->PRER |= (127<<16);//�������첽��Ƶ����λ��������λ����һ���ı䣬����������������
	
	//��������
	temp = BCD_encode(rtc_dt->year-rtc_dt->year/100,0)<<16;
	temp |= (BCD_encode(rtc_dt->week,0)&0X07)<<13;
	temp |= (BCD_encode(rtc_dt->month,0)&0X1F)<<8;
	temp |= (BCD_encode(rtc_dt->day,0)&0X3F)<<0;
	RTC->DR = temp;
	temp = 0;
	//ʱ������
	temp = (rtc_dt->pm&0X01)<<22;//24Сʱ��
	temp |= (BCD_encode(rtc_dt->hour,0)&0X3F)<<16;
	temp |= (BCD_encode(rtc_dt->minute,0)&0X7F)<<8;
	temp |= (BCD_encode(rtc_dt->second,0)&0X7F)<<0;
	RTC->TR = temp;
	
	RTC->ISR &=~ (0X01<<7);//�˳���ʼ������
	RTC->WPR =0XFF;//����д����
}

void RTC_Setting_DT(PRTC_Date rtc_dt)//���й���������ʱ������
{
	uint16 delay = 10;
	uint32 temp = 0;
	
	RTC->WPR =0XCA;
	RTC->WPR =0X53;//����д����
	RTC->ISR |= 0X01<<7;//��ʼRTC��ʼ������
	do
	{
		delay_ms(1);
		delay--;
	}while(delay&&(!(RTC->ISR&(0X01<<6))));//�ж��Ƿ��ܳ�ʼ������ʱ�˳�
	
	//��������
	temp = BCD_encode(rtc_dt->year,0)<<16;
	temp |= (BCD_encode(rtc_dt->week,0)&0X07)<<13;
	temp |= (BCD_encode(rtc_dt->month,0)&0X1F)<<8;
	temp |= (BCD_encode(rtc_dt->day,0)&0X3F)<<0;
	RTC->DR = temp;
	//ʱ������
	temp = (rtc_dt->pm&0X01)<<22;//24Сʱ��
	temp |= (BCD_encode(rtc_dt->hour,0)&0X3F)<<16;
	temp |= (BCD_encode(rtc_dt->minute,0)&0X7F)<<8;
	temp |= (BCD_encode(rtc_dt->second,0)&0X7F)<<0;
	RTC->TR = temp;
	
	RTC->ISR &=~ (0X01<<7);//�˳���ʼ������
	RTC->WPR =0XFF;//����д����

}
RTC_Date Read_DT(void)//��ȡʱ��
{
	uint32 temp = 0 ;
	RTC_Date dt ={0,0,0,0,0,0,0};//2018-7-27--17:11:30
	
	temp = RTC->DR;
	dt.year = BCD_encode((temp>>16)&0XFF,1) + 2000;
	dt.week = BCD_encode((temp>>13)&0X07,1);
	dt.month = BCD_encode((temp>>8)&0X1F,1);
	dt.day = BCD_encode((temp>>0)&0X3F,1);
	
	temp = RTC->TR;
	dt.hour = BCD_encode((temp>>16)&0XFF,1);
	dt.minute = BCD_encode((temp>>8)&0X7F,1);
	dt.second = BCD_encode((temp>>0)&0XFF,1);
	//dt.pm = BCD_encode((temp>>22)&0X001,1);//24Сʱ�Ʋ��ö�ȡ��һλ
	return dt;
}

void Show_Time(RTC_Date dt)
{		
	
	printf("%d-%d-%d\t\t����%c%c\t\t%d:%d:%d\r\n",\
	dt.year,dt.month,dt.day,Week[(dt.week-1)*2],Week[(dt.week-1)*2+1],dt.hour,dt.minute,dt.second);
}

#if  RTC_ALARM_A 
	
void RTC_ALARM_A_Init(void)
{
	uint16 delay = 10;
	uint32 alrmar = 0;
	RTC->WPR =0XCA;
	RTC->WPR =0X53;//����д����
	RTC->CR &=~ (0X01<<8);//��ֹ����A
	do
	{
		delay_ms(1);
		delay--;
	}while(delay&&(!(RTC->ISR&0X01)));//�ж�����A�Ƿ�������£���ʱ�˳�
	alrmar &=~ (0X01UL<<30);
	alrmar |=(BCD_encode(27,0)&0X3F)<<24;//27��
	alrmar |=(BCD_encode(10,0)&0X3F)<<16;//10��
	alrmar |=(BCD_encode(0,0)&0X7F)<<8;//0��
	alrmar |=(BCD_encode(30,0)&0X7F)<<0;//30��
	RTC->ALRMAR = alrmar;
	RTC->CR |= (0X01<<12);//ʹ������A�ж�
	EXTI->IMR |= 0X01<<17;//�жϲ�����
	EXTI->RTSR |= 0X01<<17;//�����ش���
	NVIC_SetPriorityGrouping(7-2); //����Ϊ��2��  
    NVIC_SetPriority(RTC_Alarm_IRQn,NVIC_EncodePriority(7-2,0,0));//�������ȼ�
	NVIC_EnableIRQ(RTC_Alarm_IRQn); 
	EXTI->PR |= (0X01<<17);//д1����жϹ����־
	RTC->ISR &=~ (0X01<<8);//�������A�жϱ�־
	RTC->CR |= (0X01<<8);//ʹ������A
	RTC->WPR =0XFF;//����д����
}
void RTC_Alarm_IRQHandler(void)
{
	
	if(EXTI->PR&(0X01<<17))
	{
		EXTI->PR |= (0X01<<17);//д1����жϹ����־
	}
	if(RTC->ISR&(0X01<<8))
	{
		RTC->ISR &=~ (0X01<<8);//�������A�жϱ�־
		printf("����A����\n");//�Ժ�Ҫ�û��ѹ��ܣ������Ըĳɱ�ģ��ж��в�Ҫ��ӡ����ʱ̫��
		
	}
	
}
#endif

#if RTC_WAKEUP
void RTC_WakeUp_Init(void)
{
	uint16 delay = 10;
	
	RTC->WPR =0XCA;
	RTC->WPR =0X53;//����д����
	RTC->CR &=~ (0X01<<10);//��ֹ����
	do
	{
		delay_ms(1);
		delay--;
	}while(delay&&(!(RTC->ISR&(0X01<<2))));//�ж�����A�Ƿ�������£���ʱ�˳�
	
	RTC->CR &=~ (0X07<<0);
	RTC->CR |=0X04<<0;//����ʱ��ѡ��
	RTC->CR |= (0X01<<14);//ʹ�ܻ����ж�
	RTC->WUTR = 2;//����ʱ������
	EXTI->IMR |= 0X01<<22;//�жϲ�����
	EXTI->RTSR |= 0X01<<22;//�����ش���
	NVIC_SetPriorityGrouping(7-2); //����Ϊ��2��  
    NVIC_SetPriority(RTC_WKUP_IRQn,NVIC_EncodePriority(7-2,0,0));//�������ȼ�
	NVIC_EnableIRQ(RTC_WKUP_IRQn); 
	EXTI->PR |= (0X01<<22);//д1����жϹ����־
	RTC->ISR &=~ (0X01<<10);//��������жϱ�־
	RTC->CR |= (0X01<<10);//ʹ�ܻ���
	RTC->WPR =0XFF;//����д����
}

void RTC_WKUP_IRQHandler(void)
{
	if(EXTI->PR&(0X01<<22))
	{
		EXTI->PR |= (0X01<<22);//д1����жϹ����־
	}
	if(RTC->ISR&(0X01<<10))
	{
		RTC->ISR &=~ (0X01<<10);//��������жϱ�־
		printf("����\n");//�Ժ�Ҫ�û��ѹ��ܣ������Ըĳɱ�ģ��ж��в�Ҫ��ӡ����ʱ̫��
	}
}

#endif
