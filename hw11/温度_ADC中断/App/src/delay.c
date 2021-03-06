#include "delay.h"
#include "led.h"
#include "usart1.h"
#if	 SysTick_EXTI 


uint16 SysTick_Count = 0;
/********************************************************************************************
*  函 数 名： SysTick_Init
*  描    述:  系统滴答定时器使用中断模式初始化
*  输入参数： 无   
*  输出参数： 无
*  返 回 值:  无
*  作    者:  付伟
*  完成日期:  2018-07-22
*  注意事项:  无
********************************************************************************************/
void SysTick_Init(void)
{
	SysTick->CTRL &=~ (0X01<<2);	//选择时钟源
	SysTick->CTRL |= (0X01<<1);		//开启中断
	SysTick->CTRL &=~ 0X01;			//关闭定时器
	SysTick->LOAD = 10*MS_BASE;		//装载数据，100ms进一次中断
	SysTick->VAL  = 0;				//把当前计数器寄存器清零（也会清除计数器标志位）
	SysTick->CTRL |= 0X01;			//打开定时器
}
/********************************************************************************************
*  函 数 名： SysTick_Handler
*  描    述:  系统滴答定时器中断服务函数。
*  输入参数： 无   
*  输出参数： 无
*  返 回 值:  无
*  作    者:  付伟
*  完成日期:  2018-07-22
*  注意事项:  无
********************************************************************************************/
void SysTick_Handler(void)
{
	if((SysTick->CTRL)&(0X01<<16))//读取该标志位，该位会自动清理
	{
//		if(Time_Out)
//		{
//			if(--Time_Out==0)
//				Flag=1;
//		}
//		
//		/*LED闪烁*/
//		if(SysTick_Count<100)
//		{
//			SysTick_Count++;
//		}
//		else
//		{
//			SysTick_Count = 0;
//			Led_State_Control(0XF0);
//		}
	}
}
#else

/********************************************************************************************
*  函 数 名： SysTick_Init
*  描    述:  系统滴答定时器不使用中断模式初始化
*  输入参数： 无   
*  输出参数： 无
*  返 回 值:  无
*  作    者:  付伟
*  完成日期:  2018-07-21
*  注意事项:  无
********************************************************************************************/
void SysTick_Init(void)
{
	SysTick->CTRL &=~ (0X01<<2);		//选择时钟源
	SysTick->CTRL &=~ (0X01<<1);		//关闭中断
}

/********************************************************************************************
*  函 数 名： delay_ms
*  描    述:  延时nms毫秒，nms最大不能超过798
*  输入参数： (uint16 nms)  
*  输出参数： 无
*  返 回 值:  无
*  作    者:  付伟
*  完成日期:  2018-07-21
*  注意事项:  SysTick->CTRL第16位为标志位，是只读的，不用写清零
********************************************************************************************/
void delay_ms(uint16 nms)
{
	uint32_t tmp;
	SysTick->CTRL &=~ 0X01;		//关闭定时器
	SysTick->LOAD = nms*MS_BASE;//装载数据
	SysTick->VAL  = 0;			//把当前计数器寄存器清零（也会清除计数器标志位）
	SysTick->CTRL |= 0X01;		//打开定时器
	do{
		tmp = SysTick->CTRL;
	}while(!(tmp&(0X01<<16)));	//判断标志位,为1则结束等待
	SysTick->CTRL &=~ 0X01;		//关闭定时器
}

/********************************************************************************************
*  函 数 名： delay_ms
*  描    述:  延时nus微秒，nus最大不能超过798915
*  输入参数： (uint32 nus)    
*  输出参数： 无
*  返 回 值:  无
*  作    者:  付伟
*  完成日期:  2018-07-21
*  注意事项:  无
********************************************************************************************/
void delay_us(uint32 nus)
{
	uint32_t tmp;
	SysTick->CTRL &=~ 0X01;		//关闭定时器
	SysTick->LOAD = nus*US_BASE;//装载数据
	SysTick->VAL  = 0;			//把当前计数器寄存器清零（也会清除计数器标志位）
	SysTick->CTRL |= 0X01;		//打开定时器
	do{
		tmp = SysTick->CTRL;
	}while(!(tmp&(0X01<<16)));	//判断标志位,为1则结束等待
	SysTick->CTRL &=~ 0X01;		//关闭定时器
}
/********************************************************************************************
*  函 数 名： delay_nms
*  描    述:  延时nms毫秒，nms最大不能超过2^32
*  输入参数： (uint32 nms)  
*  输出参数： 无
*  返 回 值:  无
*  作    者:  付伟
*  完成日期:  2018-07-21
*  注意事项:  无
********************************************************************************************/	
void delay_nms(uint32 nms)
{ 
	for(;nms>0;nms--)
	{
		delay_ms(1);
	}
}

#endif
