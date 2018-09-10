#include "AT24Cxx.h"
/********************************************************************************************
*  �� �� ���� AT24_Write_Byte
*  ��    ��:  AT24C02дһ���ֽ�����
*  ��������� д�����ݣ�д���ַ  
*  ��������� ��
*  �� �� ֵ:  0����д��ɹ���1����д��ʧ��
*  ��    ��:  ��ΰ
*  �������:  2018-07-28
*  ע������:  ��
********************************************************************************************/
uint8 AT24_Write_Byte(uint8 data,uint16 byte_addr)
{
	IIC_Start();
	IIC_Write(AT24C02_WADDR);
	if(IIC_Wait_Reply()==IIC_NO_REPLY)
	{
		return 1;
	}
	IIC_Write(byte_addr);
	if(IIC_Wait_Reply()==IIC_NO_REPLY)
	{
		return 2;
	}
	IIC_Write(data);
	if(IIC_Wait_Reply()==IIC_NO_REPLY)
	{
		return 3;
	}
	IIC_Stop();
	return 0;
}
/********************************************************************************************
*  �� �� ���� AT24_Write_Page
*  ��    ��:  AT24C02д��16���ֽ�����
*  ��������� д���������飬д����ʼ��ַ  
*  ��������� ��
*  �� �� ֵ:  0����д��ɹ���1����д��ʧ��
*  ��    ��:  ��ΰ
*  �������:  2018-07-28
*  ע������:  ÿ��ֻ��д16���ֽڣ�д������д����ȥ�����д�����ݳ���16�ֽڣ�����ͨ���������ô˺���д��
********************************************************************************************/
uint8 AT24_Write_Page(uint8 data[],uint8 byte_addr)//data[16]
{
	uint8 i;
	IIC_Start();
	IIC_Write(AT24C02_WADDR);
	if(IIC_Wait_Reply()==IIC_REPLY)
	{
		IIC_Write(byte_addr);
		if(IIC_Wait_Reply()==IIC_REPLY)
		{
			IIC_Write(data[0]);
			for(i=1;i<16;i++)
			{
				if(IIC_Wait_Reply()==IIC_REPLY)
				{
					IIC_Write(data[i]);
				}
			}
			if(IIC_Wait_Reply()==IIC_REPLY)
			{
					IIC_Stop();
					return 0;
			}
		}
			
	}
	return 1;
}
/********************************************************************************************
*  �� �� ���� AT24_Write_Continue
*  ��    ��:  �����ֽ�д
*  ��������� 
*  ��������� ��
*  �� �� ֵ: 
*  ��    ��:  ��ΰ
*  �������:  2018-07-30
*  ע������:  ��
********************************************************************************************/
/*����һ���ο��¹���˼·*/
uint8 AT24_Write_Continue(uint8 *data,uint16 nbyte, uint8 byte_addr)
{
	uint8 i,len;
	
	while(nbyte)
	{
		len = 8 - byte_addr%8;
		if(nbyte < len)
		{
			len = nbyte;
		}
		IIC_Start();
		IIC_Write(AT24C02_WADDR);
		if(IIC_Wait_Reply()==IIC_NO_REPLY)
		{
			return 1;
		}
		IIC_Write(byte_addr);
		if(IIC_Wait_Reply()==IIC_NO_REPLY)
		{
			return 2;
		}

		for(i=0;i<8;i++)
		{
			IIC_Write(*(data+i));
			if(IIC_Wait_Reply()==IIC_NO_REPLY)
			{
				return 3;
			}
		}
		IIC_Stop();		
		delay_ms(5);
		byte_addr += len;
		data += len;
		nbyte -=len; 
	}
	return 0;
}

/********************************************************************************************
*  �� �� ���� AT24_Read_Byte
*  ��    ��:  AT24C02��ȡָ����ַһ�ֽ�����
*  ��������� ���ݵ�ַ  
*  ��������� ��
*  �� �� ֵ:  ��ȡ������ֵ
*  ��    ��:  ��ΰ
*  �������:  2018-07-28
*  ע������:  ��
********************************************************************************************/
uint8 AT24_Read_Byte(uint8 byte_addr,uint8 *data)
{
	IIC_Start();
	IIC_Write(AT24C02_WADDR);
	if(IIC_Wait_Reply()==IIC_NO_REPLY)
	{
		return 1;
	}
	IIC_Write(byte_addr);
	if(IIC_Wait_Reply()==IIC_NO_REPLY)
	{
		return 2;
	}
	IIC_Start();
	IIC_Write(AT24C02_RADDR);
	if(IIC_Wait_Reply()==IIC_NO_REPLY)
	{
		return 3;
	}
	*data = IIC_Read();
	IIC_Write_Reply(IIC_NO_REPLY);
	IIC_Stop();
		
	return 0;
}
/********************************************************************************************
*  �� �� ���� AT24_Read_Continue
*  ��    ��:  AT24C02������ȡnbyte�ֽ�����
*  ��������� ��ȡ���ݴ������飬��ȡ���ݳ��ȣ�byte������ȡ��ʼ��ַ  
*  ��������� ��
*  �� �� ֵ:  ��
*  ��    ��:  ��ΰ
*  �������:  2018-07-30
*  ע������:  ��
********************************************************************************************/
uint8 AT24_Read_Continue(uint8 *data,uint16 nbyte, uint8 byte_addr)
{
	uint16 i; //�����ֽ������256�������ܶ���Ϊuint8
	IIC_Start();
	IIC_Write(AT24C02_WADDR);
	if(IIC_Wait_Reply()==IIC_NO_REPLY)
	{
		return 1;
	}
	IIC_Write(byte_addr);
	if(IIC_Wait_Reply()==IIC_NO_REPLY)
	{
		return 2;
	}
	IIC_Start();
	IIC_Write(AT24C02_RADDR);
	if(IIC_Wait_Reply()==IIC_NO_REPLY)
	{
		return 3;
	}	
	for(i=0;i<nbyte;i++)
	{
		*(data+i) = IIC_Read();
		if(i == nbyte - 1)
		{
			IIC_Write_Reply(IIC_NO_REPLY);
			IIC_Stop();
		}
		else
		{
			IIC_Write_Reply(IIC_REPLY);
		}
	}
	return 0;
}

void AT24C02_Clear(void)
{
	uint8 zero[256];
	memset(zero,0,256);
	AT24_Write_Continue(zero,256,0X00);
	delay_nms(5);
}
	
