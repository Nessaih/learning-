#include "can.h"


void Can_Configuration(void)
{
	uint8 delay = 50;
	//double NominalBitTime,TQ;
	uint16 BRP90;
	//CAN2����RX��TX���ÿ���
	RCC->AHB1ENR = 0X01<<1;//PBʱ�ӿ���
	GPIOB->MODER &=~ ((0X10<<12)|(0X10<<13));
	GPIOB->MODER |= (0X10<<12)|(0X10<<13);
	GPIOB->OSPEEDR &=~ ((0X10<<12)|(0X10<<13));
	GPIOB->OSPEEDR |= 0X01<<13;//25Mhz����ٶ�
	GPIOB->PUPDR &=~ ((0X10<<12)|(0X10<<13));
	GPIOB->PUPDR &=~ ((0X01<<12)|(0X01<<13));//�˿�����
	
	//CAN��ؼĴ�������
	RCC->APB1ENR = 0X01<<26;//can2ʱ�ӿ���
	CAN2->MCR |= (0X01<<6)|(0X01<<3)|(0X01);	/*Ӳ���Զ����128��11������λ���˳����߹ر�״̬;
												FIFO���������Ƚ��վ���Ϣ;
												CAN�����ʼ��ģʽ�������޸�BTR�Ĵ���.*/
	
	do{
		delay_ms(1);
	}
	while(!(CAN2->MSR&0X01)&&delay);//
	
//	NominalBitTime = 1/BaudRate;
//	TQ = NominalBitTime/TQ_NUM;
//	BRP90 = TQ*42000000-1;
	BRP90 = 42000/(BaudRate*TQ_NUM)-1;
	CAN2->TSR |= (BRP90&0X1FF);
	CAN2->TSR |=(0X07<<16)|(0X06<<20);//1,8,7
	CAN2->MCR &=~ 0X01;//�˳���ʼ��ģʽ
	
	CAN2->FMR |= 0X01;//ɸѡ����ʼ��
	CAN2->FM1R |= 0XFFFFFFF;//�б�ģʽ
	CAN2->FFA1R &=~ 0X01;//ɸѡ��0���䵽FIFO 0;
	CAN2->FA1R |= 0X01;//����ɸѡ��0
	CAN2->FMR &=~ 0X01;//ɸѡ���˳���ʼ��
}
