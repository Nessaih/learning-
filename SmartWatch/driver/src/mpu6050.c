#include "mpu6050.h"
#include "delay.h"  
#include "rtc.h"
#include "stepAlgorithm.h"
#include "watchInfo.h"
#include "oled_screen.h"
/***********************************************************************************************************************
Copyright 2008 - 2016 深圳市信盈达电子有限公司. All rights reserved.
文件名:        mpu6050.c
描述   :       mpu6050驱动文件
作者   :       Jahol Fan
版本   :       V1.0
修改   :   
完成日期：     2016.10.13
Notice    :本程序只供学习使用，未经作者许可，不得用于其它任何用途
信盈达官网：http://www.edu118.com/
信盈达网校：http://www.edu118.cn/
版权所有，盗版必究。
************************************************************************************************************************/
//初始化MPU6050
//返回值:0,成功
//    其他,错误代码
u8 MPU_Init(void)
{ 
  u8 res;
  //IIC_init();//初始化IIC总线
  MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X80);	//复位MPU6050
  delay_ms(100);  //Jahol Fan ：奇怪的问题，延时改长了，就不能兼容HP-6
  MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X00);	//唤醒MPU6050 
  //MPU_Set_Gyro_Fsr(3);					//陀螺仪传感器,±2000dps
  MPU_Set_Accel_Fsr(0);					//加速度传感器,±2g
  MPU_Set_Rate(50);						//设置采样率50Hz
  MPU_Write_Byte(MPU_INT_EN_REG,0X00);	//关闭所有中断
  MPU_Write_Byte(MPU_USER_CTRL_REG,0X00);	//I2C主模式关闭
  MPU_Write_Byte(MPU_FIFO_EN_REG,0X00);	//关闭FIFO
  MPU_Write_Byte(MPU_INTBP_CFG_REG,0X80);	//INT引脚低电平有效
  res=MPU_Read_Byte(MPU_DEVICE_ID_REG);
  if(res==MPU_ADDR)//器件ID正确
  {
    MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X01);	//设置CLKSEL,PLL X轴为参考
    MPU_Write_Byte(MPU_PWR_MGMT2_REG,0x07);	//只有加速度都工作
    MPU_Set_Rate(50);						            //设置采样率为50Hz
    
  }else return 1;
  return 0;
}
//设置MPU6050陀螺仪传感器满量程范围
//fsr:0,±250dps;1,±500dps;2,±1000dps;3,±2000dps
//返回值:0,设置成功
//    其他,设置失败 
u8 MPU_Set_Gyro_Fsr(u8 fsr)
{
  return MPU_Write_Byte(MPU_GYRO_CFG_REG,fsr<<3);//设置陀螺仪满量程范围  
}
//设置MPU6050加速度传感器满量程范围
//fsr:0,±2g;1,±4g;2,±8g;3,±16g
//返回值:0,设置成功
//    其他,设置失败 
u8 MPU_Set_Accel_Fsr(u8 fsr)
{
  return MPU_Write_Byte(MPU_ACCEL_CFG_REG,fsr<<3);//设置加速度传感器满量程范围  
}
//设置MPU6050的数字低通滤波器
//lpf:数字低通滤波频率(Hz)
//返回值:0,设置成功
//    其他,设置失败 
u8 MPU_Set_LPF(u16 lpf)
{
  u8 data=0;
  if(lpf>=188)data=1;
  else if(lpf>=98)data=2;
  else if(lpf>=42)data=3;
  else if(lpf>=20)data=4;
  else if(lpf>=10)data=5;
  else data=6; 
  return MPU_Write_Byte(MPU_CFG_REG,data);//设置数字低通滤波器  
}
//设置MPU6050的采样率(假定Fs=1KHz)
//rate:4~1000(Hz)
//返回值:0,设置成功
//    其他,设置失败 
u8 MPU_Set_Rate(u16 rate)
{
  u8 data;
  if(rate>1000)rate=1000;
  if(rate<4)rate=4;
  data=1000/rate-1;
  data=MPU_Write_Byte(MPU_SAMPLE_RATE_REG,data);	//设置数字低通滤波器
  return MPU_Set_LPF(rate/2);	//自动设置LPF为采样率的一半
}

//得到温度值
//返回值:温度值(扩大了100倍)
short MPU_Get_Temperature(void)
{
  u8 buf[2]; 
  short raw;
  float temp;
  MPU_Read_Len(MPU_ADDR,MPU_TEMP_OUTH_REG,2,buf); 
  raw=((u16)buf[0]<<8)|buf[1];  
  temp=36.53+((double)raw)/340;  
  return temp*100;
}
//得到陀螺仪值(原始值)
//gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
//返回值:0,成功
//    其他,错误代码
u8 MPU_Get_Gyroscope(short *gx,short *gy,short *gz)
{
  u8 buf[6],res;  
  res=MPU_Read_Len(MPU_ADDR,MPU_GYRO_XOUTH_REG,6,buf);
  if(res==0)
  {
    *gx=((u16)buf[0]<<8)|buf[1];  
    *gy=((u16)buf[2]<<8)|buf[3];  
    *gz=((u16)buf[4]<<8)|buf[5];
  } 	
  return res;;
}
//得到加速度值(原始值)
//gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
//返回值:0,成功
//    其他,错误代码
u8 MPU_Get_Accelerometer(short *ax,short *ay,short *az)
{
  u8 buf[6],res;  
  res=MPU_Read_Len(MPU_ADDR,MPU_ACCEL_XOUTH_REG,6,buf);
  if(res==0)
  {
    *ax=((u16)buf[0]<<8)|buf[1];  
    *ay=((u16)buf[2]<<8)|buf[3];  
    *az=((u16)buf[4]<<8)|buf[5];
  } 	
  return res;;
}
//IIC连续写
//addr:器件地址 
//reg:寄存器地址
//len:写入长度
//buf:数据区
//返回值:0,正常
//    其他,错误代码
u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{
  u8 i; 
  IIC_Start(); 
  IIC_WriteByte((addr<<1)|0);//发送器件地址+写命令	
  IIC_WriteByte(reg);	//写寄存器地址
  for(i=0;i<len;i++)
  {
    IIC_WriteByte(buf[i]);	//发送数据	
  }    
  IIC_Stop();	 
  return 0;	
} 
//IIC连续读
//addr:器件地址
//reg:要读取的寄存器地址
//len:要读取的长度
//buf:读取到的数据存储区
//返回值:0,正常
//    其他,错误代码
u8 MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{ 
  IIC_Start(); 
  IIC_WriteByte((addr<<1)|0);//发送器件地址+写命令	
  IIC_WriteByte(reg);	//写寄存器地址
  IIC_Start();
  IIC_WriteByte((addr<<1)|1);//发送器件地址+读命令	
  while(len)
  {
    //if(len==1)*buf=IIC_ReadByte(0);//读数据,发送nACK 
    //else *buf=IIC_ReadByte(1);		//读数据,发送ACK  
    if(len==1)*buf=IIC_ReadByte(1);//读数据,发送nACK 
    else *buf=IIC_ReadByte(0);		//读数据,发送ACK  
    
    len--;
    buf++; 
  }    
  IIC_Stop();	//产生一个停止条件 
  return 0;	
}
//IIC写一个字节 
//reg:寄存器地址
//data:数据
//返回值:0,正常
//    其他,错误代码
u8 MPU_Write_Byte(u8 reg,u8 data) 				 
{ 
  IIC_Start(); 
  IIC_WriteByte((MPU_ADDR<<1)|0);//发送器件地址+写命令	
  IIC_WriteByte(reg);	//写寄存器地址
  IIC_WriteByte(data);//发送数据 
  IIC_Stop();	 
  return 0;
}
//IIC读一个字节 
//reg:寄存器地址 
//返回值:读到的数据
u8 MPU_Read_Byte(u8 reg)
{
  u8 res;
  IIC_Start(); 
  IIC_WriteByte((MPU_ADDR<<1)|0);//发送器件地址+写命令	
  IIC_WriteByte(reg);	//写寄存器地址
  IIC_Start();
  IIC_WriteByte((MPU_ADDR<<1)|1);//发送器件地址+读命令	
  res=IIC_ReadByte(1);//读取数据,发送nACK 
  IIC_Stop();			//产生一个停止条件 
  return res;		
}

void MPU_Show(void)
{
	
	/**********************************计步相关参数定义***********************************/
	u8 err;
	u8 uiBuf[40];
	accValue_t accValue;
	static sportsInfo_t userSportsInfo;
	static u8 time_cnt;
	static timeStamp_t timeStamp;
	short aacx,aacy,aacz;									//加速度传感器原始数据
	static u8 tempSecond;	
	static uint8 flag = 1;
	RTC_Date rtcTime_daat;
	RTC_Date *rtcTime = &rtcTime_daat;
	/**********************************计步相关参数定义***********************************/
	if(flag)
	{
		MPU_Init();
		WatchInfo_init();
		MPU_Get_Accelerometer(&aacx,&aacy,&aacz);
		flag = 0;
	}
	else
	{
		MPU_Get_Accelerometer(&aacx,&aacy,&aacz);			  //得到加速度传感器数据
		rtcTime_daat = Read_DT(); 					  //获取当前RTC的值
		
		if(tempSecond != timeStamp.second)					 //秒更新
		{
			tempSecond = timeStamp.second;
			timeStamp.twentyMsCount = 0 ;//20ms计数变量清零
		}
		else												  //秒不更新，1秒等于50*20ms
		{
			timeStamp.twentyMsCount ++;//20ms计数变量++
		}
		
		timeStamp.hour	 = rtcTime->hour;
		timeStamp.minute = rtcTime->minute;
		timeStamp.second = rtcTime->second;
		
		//将三轴数据转换为以g为单位的数据
		accValue.accX = ((float)(int)aacx/16384) *10;
		accValue.accY = ((float)(int)aacy/16384) *10;
		accValue.accZ = ((float)(int)aacz/16384) *10; 
		userSportsInfo = *onSensorChanged(&accValue,&timeStamp,WatchInfo_getUserInfo(&err)); //调用计数算法
		
		sprintf((char*)uiBuf,"Step:%05d ",userSportsInfo.stepCount); // 显示步数
		OLED_Show_String(0,10,(char *)uiBuf,CH_SIZE1,normal); 
		sprintf((char*)uiBuf,"kal:%.1f KAL",userSportsInfo.calories); // 显示卡路里
		OLED_Show_String(2,10,(char *)uiBuf,CH_SIZE1,normal); 	
		sprintf((char*)uiBuf,"dis:%.1f M",userSportsInfo.distance); // 显示里程
		OLED_Show_String(4,10,(char *)uiBuf,CH_SIZE1,normal); 			
	
		if(accValue.accZ>=0)
		{
			sprintf((char*)uiBuf,"Z:%02d m/s^2",(char)accValue.accZ); // 以整数显示
			OLED_Show_String(6,10,(char *)uiBuf,CH_SIZE1,normal);				
		}
	  else
		{
			sprintf((char*)uiBuf,"Z:-%02d",(char)(-accValue.accZ)); // 以整数显示
			OLED_Show_String(6,10,(char *)uiBuf,CH_SIZE1,normal);
		}		

	}
		delay_ms(20);//以50Hz的频率去读取三轴加速度的XYZ轴加速度值
}
