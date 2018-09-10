#ifndef __DELAY_H_
#define __DELAY_H_

#include "stm32f4xx.h"
#include "type.h"
#include "usart.h"
#include "led.h"
#include "key.h"

#define MS_BASE 1000
#define US_BASE 1

extern void Time10_Configuration(void);
extern void delay_ms(uint16 nms);
extern void delay_us(uint16 nus);
extern void delay_nms(uint32 nms);
#endif



