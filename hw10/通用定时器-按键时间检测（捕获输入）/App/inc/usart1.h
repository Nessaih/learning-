#ifndef __USART1__H_
#define __USART1__H_
#include "stm32f4xx.h"
#include "stdio.h"
#include "string.h"
#include "led.h"
#include "type.h"

//��������������һҪ��.0,��ʾ������
#define FCK  84000000		//USART1ʱ����RCC_APB2:84MHzʱ��
#define BAUD_RATE  9600.0		//������
#define MAX_LEN		512

extern uint8 Flag,Time_Out;

extern void Usart1_Init(void);
extern void Byte_Send(uint8 Msg);
extern void Str_Send(uint8 *Str);
extern uint8 Byte_Receive(void);
extern void Str_Receive(void);
extern void Led_Switch(void);
extern void B2S(uint8 *Str);

#endif
