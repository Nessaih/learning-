#ifndef __USART1__H_
#define __USART1__H_
#include "stm32f4xx.h"
#include "type.h"

//��������������һҪ��.0,��ʾ������
#define FCK  84000000		//USART1ʱ����RCC_APB2:84MHzʱ��
#define BAUD_RATE  9600.0		//������


extern void Usart1_Init(void);
extern void Usart1_Send(uint8 Msg);
extern void Usart1_Str_Send(uint8 Str[]);
extern uint8 Usart1_Receive(void);

#endif
