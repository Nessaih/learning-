#ifndef __SHT20_H_
#define __SHT20_H_

#include "stm32f4xx.h"
#include "type.h"
#include "sys.h"
#include "delay.h"
#include "iic.h"
#define SHT20_RESET			 0XFE		 //��λ����
#define MEASURE_TEMPERATURE  0XF3        //�����¶Ȳ�������
#define MEASURE_HUMIDITY 	 0XF5        //����ʪ�Ȳ�������
#define SHT20ADDR_W     	 0X80        //SHT20д��ַ
#define SHT20ADDR_R    		 0X81        //SHT20����ַ

extern void SHT20_Init(void);
extern uint8 SHT20_Write_CMD(uint8 cmd);
extern uint8 SHT20_Calculation(double *data,uint8 cmd);
extern void SHT20_Print(void);
extern void SHT20_Show(void);
#endif
