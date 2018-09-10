#include "stm32f4xx.h"
#include "includes.h"
#include "os_cpu.h"
#include "type.h"
#include "Start_Task.h"
#include "led.h"
#include "USART.H"



/********************************************************************************************
*  �� �� ���� SysTick_Handler
*  ��    ��:  ϵͳ�δ��ж�
*  ��������� ��   
*  ��������� ��
*  �� �� ֵ:  ��
*  ��    ��:  �±�
*  �������:  2018-06-20
*  ע������:  ʱ�����
********************************************************************************************/
void SysTick_Handler(void)
{	
	OSIntEnter();						//�����ж�
	OSTimeTick();       				//����ucos��ʱ�ӷ������               
	OSIntExit();       	 				//���������л����ж�
}

			   
/********************************************************************************************
*  �� �� ���� OS_SysTick_init
*  ��    ��:  ϵͳ�δ��ʼ��
*  ��������� uint32 nms����ý���һ���ж�,uint8 SYSCLK��ʱ��168MHZ 
*  ��������� ��
*  �� �� ֵ:  ��
*  ��    ��:  �±�
*  �������:  2018-06-20
*  ע������:  ʱ�����
********************************************************************************************/
void OS_SysTick_init(uint32 nms,uint8 SYSCLK)
{
 	SysTick->CTRL&=~(0X01<<2);					//SYSTICKʹ���ⲿʱ��Դ	   
	SysTick->CTRL|=0X01<<1;   					//����SYSTICK�ж�
	SysTick->LOAD=nms * SYSCLK *1000/8; 	   //ÿ1/delay_ostickspersec���ж�һ��	
	SysTick->CTRL|=0X01<<0;   					//����SYSTICK  
	/* �����ж�Դ���ȼ� */
	NVIC_SetPriority(SysTick_IRQn,NVIC_EncodePriority((7-3),0,0));   //����ϵͳ�δ��ж����ȼ�
}


int main(void)
{
    u8 i;
    u8 cpu_sr;
    OSInit();    //��ʼ������ϵͳ
      
    Led_Io_Init();
    usart_Io_Init();    
    USART1_SET(115200);


    OS_SysTick_init(1000/OS_TICKS_PER_SEC,168);//ʱ��Ƭ����
    
    OS_ENTER_CRITICAL();//�����ٽ�������ֹ���жϴ��
    
    //���������������ٴ���һ������
    i=OSTaskCreate(Start_Task,NULL,&Start_Task_STK[START_TASK_STACK_SIZE-1],START_TASK_STACK_PRIO); 
    printf("%d\r\n",i);

    OS_EXIT_CRITICAL();// �˳��ٽ����� �����жϴ��
    OSStart();        //����ϵͳ����
}





