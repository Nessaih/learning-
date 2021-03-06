#ifndef __RTC_H_
#define __RTC_H_

#include "stm32f4xx.h"
#include "delay.h"
#include "type.h"
#include "usart.h"
#include "string.h"

#define RTC_ALARM_A 0
#define RTC_WAKEUP 0

typedef struct RD{
	uint8 year;
	uint8 month;
	uint8 day;
	uint8 week;
	
	uint8 hour;
	uint8 minute; 
	uint8 second;
	uint8 pm;
}RTC_Date,*PRTC_Date;

typedef	struct
{
	u8 hour;
	u8 minute;
	u8 second;
	u8 twentyMsCount;
}timeStamp_t;

extern char Week[15];

extern void RTC_Init(void);
extern uint8 BCD_encode(uint8 num,uint8 flag);
extern void RTC_Setting(RTC_Date rtc_dt);//上电设置时间日期
extern void RTC_Setting_DT(RTC_Date rtc_dt);//运行过程中设置时间日期
extern RTC_Date Read_DT(void);
extern void Print_Time(void);
extern void Show_Time(void);
extern RTC_Date isDate_Time(uint8 dt[]);
extern void Usart_Setting_DT(void);

#if  RTC_ALARM_A 
extern void RTC_ALARM_A_Init(void);
#endif
#if  RTC_WAKEUP 
extern void RTC_WakeUp_Init(void);
#endif


#endif
