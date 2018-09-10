#include "sram.h"

void SRAM_Init(void)
{
	/*IO�ڳ�ʼ������Ϊ���ù��ܣ�PD0,1,4,5,8��15��PE0,1,7��15��//PF0��5,12��15��/PG0��5,10*/	
	RCC->AHB1ENR|=0XF<<3;    	//ʹ��PD,PE,PF,PGʱ��  
	GPIOD->MODER |=0XAAAA0A0A;  //���óɸ������
	GPIOE->MODER |=0XAAAA800A;  //���óɸ������
	GPIOF->MODER |=0XAA000AAA;  //���óɸ������
	GPIOG->MODER |=0X00200AAA;  //���óɸ������
	GPIOE->OSPEEDR |=0XFFFFC00F;   //���ó��������100M
	GPIOF->OSPEEDR |=0XFF000FFF;   //���ó��������100M
	GPIOG->OSPEEDR |=0X00300FFF;   //���ó��������100M

	/*���ù���ѡ��FSMC*/
	GPIOD->AFR[0] = 0X00CC00CC;         
	GPIOD->AFR[1] = 0XCCCCCCCC;
	GPIOE->AFR[0] = 0XC00000CC;         
	GPIOE->AFR[1] = 0XCCCCCCCC;
	GPIOF->AFR[0] = 0X00CCCCCC;         
	GPIOF->AFR[1] = 0XCCCC0000;
	GPIOG->AFR[0] = 0X00CCCCCC;         
	GPIOG->AFR[1] = 0X00000C00;

	/*FSMC�Ĵ�������*/
	RCC->AHB3ENR|=1<<0;   
	FSMC_Bank1_BCR |= (0X01<<12)|(0X01<<1);//дʹ��;45λĬ��16λ���ݿ�ȣ���ַ�������߷Ǹ���
	FSMC_Bank1_BTR &=~(0X0F<<20);//ʱ�Ӳ���Ƶ
	FSMC_Bank1_BTR |= 0X08<<8;//���ݱ���ʱ��9*6ns = 54��55
	FSMC_Bank1_BTR &=~(0X0F<<4);//��ַ����ʱ��0
	FSMC_Bank1_BTR &=~(0X0F<<0);//������ַʱ��0
	FSMC_Bank1_BCR |=1<<0; 	//ʹ��
}

