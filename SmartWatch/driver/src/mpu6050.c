#include "mpu6050.h"
#include "delay.h"  
#include "rtc.h"
#include "stepAlgorithm.h"
#include "watchInfo.h"
#include "oled_screen.h"
/***********************************************************************************************************************
Copyright 2008 - 2016 ��������ӯ��������޹�˾. All rights reserved.
�ļ���:        mpu6050.c
����   :       mpu6050�����ļ�
����   :       Jahol Fan
�汾   :       V1.0
�޸�   :   
������ڣ�     2016.10.13
Notice    :������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
��ӯ�������http://www.edu118.com/
��ӯ����У��http://www.edu118.cn/
��Ȩ���У�����ؾ���
************************************************************************************************************************/
//��ʼ��MPU6050
//����ֵ:0,�ɹ�
//    ����,�������
u8 MPU_Init(void)
{ 
  u8 res;
  //IIC_init();//��ʼ��IIC����
  MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X80);	//��λMPU6050
  delay_ms(100);  //Jahol Fan ����ֵ����⣬��ʱ�ĳ��ˣ��Ͳ��ܼ���HP-6
  MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X00);	//����MPU6050 
  //MPU_Set_Gyro_Fsr(3);					//�����Ǵ�����,��2000dps
  MPU_Set_Accel_Fsr(0);					//���ٶȴ�����,��2g
  MPU_Set_Rate(50);						//���ò�����50Hz
  MPU_Write_Byte(MPU_INT_EN_REG,0X00);	//�ر������ж�
  MPU_Write_Byte(MPU_USER_CTRL_REG,0X00);	//I2C��ģʽ�ر�
  MPU_Write_Byte(MPU_FIFO_EN_REG,0X00);	//�ر�FIFO
  MPU_Write_Byte(MPU_INTBP_CFG_REG,0X80);	//INT���ŵ͵�ƽ��Ч
  res=MPU_Read_Byte(MPU_DEVICE_ID_REG);
  if(res==MPU_ADDR)//����ID��ȷ
  {
    MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X01);	//����CLKSEL,PLL X��Ϊ�ο�
    MPU_Write_Byte(MPU_PWR_MGMT2_REG,0x07);	//ֻ�м��ٶȶ�����
    MPU_Set_Rate(50);						            //���ò�����Ϊ50Hz
    
  }else return 1;
  return 0;
}
//����MPU6050�����Ǵ����������̷�Χ
//fsr:0,��250dps;1,��500dps;2,��1000dps;3,��2000dps
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
u8 MPU_Set_Gyro_Fsr(u8 fsr)
{
  return MPU_Write_Byte(MPU_GYRO_CFG_REG,fsr<<3);//���������������̷�Χ  
}
//����MPU6050���ٶȴ����������̷�Χ
//fsr:0,��2g;1,��4g;2,��8g;3,��16g
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
u8 MPU_Set_Accel_Fsr(u8 fsr)
{
  return MPU_Write_Byte(MPU_ACCEL_CFG_REG,fsr<<3);//���ü��ٶȴ����������̷�Χ  
}
//����MPU6050�����ֵ�ͨ�˲���
//lpf:���ֵ�ͨ�˲�Ƶ��(Hz)
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
u8 MPU_Set_LPF(u16 lpf)
{
  u8 data=0;
  if(lpf>=188)data=1;
  else if(lpf>=98)data=2;
  else if(lpf>=42)data=3;
  else if(lpf>=20)data=4;
  else if(lpf>=10)data=5;
  else data=6; 
  return MPU_Write_Byte(MPU_CFG_REG,data);//�������ֵ�ͨ�˲���  
}
//����MPU6050�Ĳ�����(�ٶ�Fs=1KHz)
//rate:4~1000(Hz)
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
u8 MPU_Set_Rate(u16 rate)
{
  u8 data;
  if(rate>1000)rate=1000;
  if(rate<4)rate=4;
  data=1000/rate-1;
  data=MPU_Write_Byte(MPU_SAMPLE_RATE_REG,data);	//�������ֵ�ͨ�˲���
  return MPU_Set_LPF(rate/2);	//�Զ�����LPFΪ�����ʵ�һ��
}

//�õ��¶�ֵ
//����ֵ:�¶�ֵ(������100��)
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
//�õ�������ֵ(ԭʼֵ)
//gx,gy,gz:������x,y,z���ԭʼ����(������)
//����ֵ:0,�ɹ�
//    ����,�������
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
//�õ����ٶ�ֵ(ԭʼֵ)
//gx,gy,gz:������x,y,z���ԭʼ����(������)
//����ֵ:0,�ɹ�
//    ����,�������
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
//IIC����д
//addr:������ַ 
//reg:�Ĵ�����ַ
//len:д�볤��
//buf:������
//����ֵ:0,����
//    ����,�������
u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{
  u8 i; 
  IIC_Start(); 
  IIC_WriteByte((addr<<1)|0);//����������ַ+д����	
  IIC_WriteByte(reg);	//д�Ĵ�����ַ
  for(i=0;i<len;i++)
  {
    IIC_WriteByte(buf[i]);	//��������	
  }    
  IIC_Stop();	 
  return 0;	
} 
//IIC������
//addr:������ַ
//reg:Ҫ��ȡ�ļĴ�����ַ
//len:Ҫ��ȡ�ĳ���
//buf:��ȡ�������ݴ洢��
//����ֵ:0,����
//    ����,�������
u8 MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{ 
  IIC_Start(); 
  IIC_WriteByte((addr<<1)|0);//����������ַ+д����	
  IIC_WriteByte(reg);	//д�Ĵ�����ַ
  IIC_Start();
  IIC_WriteByte((addr<<1)|1);//����������ַ+������	
  while(len)
  {
    //if(len==1)*buf=IIC_ReadByte(0);//������,����nACK 
    //else *buf=IIC_ReadByte(1);		//������,����ACK  
    if(len==1)*buf=IIC_ReadByte(1);//������,����nACK 
    else *buf=IIC_ReadByte(0);		//������,����ACK  
    
    len--;
    buf++; 
  }    
  IIC_Stop();	//����һ��ֹͣ���� 
  return 0;	
}
//IICдһ���ֽ� 
//reg:�Ĵ�����ַ
//data:����
//����ֵ:0,����
//    ����,�������
u8 MPU_Write_Byte(u8 reg,u8 data) 				 
{ 
  IIC_Start(); 
  IIC_WriteByte((MPU_ADDR<<1)|0);//����������ַ+д����	
  IIC_WriteByte(reg);	//д�Ĵ�����ַ
  IIC_WriteByte(data);//�������� 
  IIC_Stop();	 
  return 0;
}
//IIC��һ���ֽ� 
//reg:�Ĵ�����ַ 
//����ֵ:����������
u8 MPU_Read_Byte(u8 reg)
{
  u8 res;
  IIC_Start(); 
  IIC_WriteByte((MPU_ADDR<<1)|0);//����������ַ+д����	
  IIC_WriteByte(reg);	//д�Ĵ�����ַ
  IIC_Start();
  IIC_WriteByte((MPU_ADDR<<1)|1);//����������ַ+������	
  res=IIC_ReadByte(1);//��ȡ����,����nACK 
  IIC_Stop();			//����һ��ֹͣ���� 
  return res;		
}

void MPU_Show(void)
{
	
	/**********************************�Ʋ���ز�������***********************************/
	u8 err;
	u8 uiBuf[40];
	accValue_t accValue;
	static sportsInfo_t userSportsInfo;
	static u8 time_cnt;
	static timeStamp_t timeStamp;
	short aacx,aacy,aacz;									//���ٶȴ�����ԭʼ����
	static u8 tempSecond;	
	static uint8 flag = 1;
	RTC_Date rtcTime_daat;
	RTC_Date *rtcTime = &rtcTime_daat;
	/**********************************�Ʋ���ز�������***********************************/
	if(flag)
	{
		MPU_Init();
		WatchInfo_init();
		MPU_Get_Accelerometer(&aacx,&aacy,&aacz);
		flag = 0;
	}
	else
	{
		MPU_Get_Accelerometer(&aacx,&aacy,&aacz);			  //�õ����ٶȴ���������
		rtcTime_daat = Read_DT(); 					  //��ȡ��ǰRTC��ֵ
		
		if(tempSecond != timeStamp.second)					 //�����
		{
			tempSecond = timeStamp.second;
			timeStamp.twentyMsCount = 0 ;//20ms������������
		}
		else												  //�벻���£�1�����50*20ms
		{
			timeStamp.twentyMsCount ++;//20ms��������++
		}
		
		timeStamp.hour	 = rtcTime->hour;
		timeStamp.minute = rtcTime->minute;
		timeStamp.second = rtcTime->second;
		
		//����������ת��Ϊ��gΪ��λ������
		accValue.accX = ((float)(int)aacx/16384) *10;
		accValue.accY = ((float)(int)aacy/16384) *10;
		accValue.accZ = ((float)(int)aacz/16384) *10; 
		userSportsInfo = *onSensorChanged(&accValue,&timeStamp,WatchInfo_getUserInfo(&err)); //���ü����㷨
		
		sprintf((char*)uiBuf,"Step:%05d ",userSportsInfo.stepCount); // ��ʾ����
		OLED_Show_String(0,10,(char *)uiBuf,CH_SIZE1,normal); 
		sprintf((char*)uiBuf,"kal:%.1f KAL",userSportsInfo.calories); // ��ʾ��·��
		OLED_Show_String(2,10,(char *)uiBuf,CH_SIZE1,normal); 	
		sprintf((char*)uiBuf,"dis:%.1f M",userSportsInfo.distance); // ��ʾ���
		OLED_Show_String(4,10,(char *)uiBuf,CH_SIZE1,normal); 			
	
		if(accValue.accZ>=0)
		{
			sprintf((char*)uiBuf,"Z:%02d m/s^2",(char)accValue.accZ); // ��������ʾ
			OLED_Show_String(6,10,(char *)uiBuf,CH_SIZE1,normal);				
		}
	  else
		{
			sprintf((char*)uiBuf,"Z:-%02d",(char)(-accValue.accZ)); // ��������ʾ
			OLED_Show_String(6,10,(char *)uiBuf,CH_SIZE1,normal);
		}		

	}
		delay_ms(20);//��50Hz��Ƶ��ȥ��ȡ������ٶȵ�XYZ����ٶ�ֵ
}
