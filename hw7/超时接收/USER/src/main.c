#include "stm32f4xx.h"
#include "led.h"
#include "Beep.h"
#include "key.h"
#include "usart1.h"
#include "EXTI.h"
#include "delay.h"
int main(void)    
{

	unsigned char msg[]="FUwei123 \n";

	Led_Io_Init();
//    Beep_Io_Init();
//    Key_Io_Init();
	Usart1_Init();
	SysTick_Init();
	Led_State_Control(0x0f);
	Led_State_Control(0xc0);
//	Beep_State_Control(0);
//	B2S(msg);
//	Str_Send(msg);
	EXTI_Configration();
//	printf("fuwei ni hao !\n");
    while(1)
    {
		Led_Switch();//����ledȡ��
		
    } 
           
}


