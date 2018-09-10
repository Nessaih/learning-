#include "oled_screen.h"
#include "font.h"
#include "stdlib.h"

void OLED_Io_Init(void)
{
	RCC->AHB1ENR |= 3<<0;//PA  PB
	
	//OLED_RES  	PB13
	GPIOB->MODER &= ~(3<<26);
	GPIOB->MODER |= 1<<26;
	
	GPIOB->OTYPER &= ~(1<<13);
	GPIOB->OSPEEDR &= ~(3<<26);
	GPIOB->OSPEEDR |= 2<<26;
	
	//OLED_DC 		PA15
	GPIOA->MODER &= ~(3ul<<30);
	GPIOA->MODER |= 1ul<<30;
	
	GPIOA->OTYPER &= ~(1<<15);
	GPIOA->OSPEEDR &= ~(3ul<<30);
	GPIOA->OSPEEDR |= 2ul<<30;
	
	//OLED_CS  		PB7
	GPIOB->MODER &= ~(3<<14);
	GPIOB->MODER |= 1<<14;
	
	GPIOB->OTYPER &= ~(1<<7);
	GPIOB->OSPEEDR &= ~(3<<14);
	GPIOB->OSPEEDR |= 2<<14;	
}				    
void OLED_Init(void)
{ 	Spi_Io_Init();
	OLED_Io_Init();	
	OLED_CS_SET;//Ƭѡ�ͷ�,SPI��ѡ����Ļ
	OLED_Reset();		
	
	OLED_Write_Byte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_Write_Byte(0x02,OLED_CMD);//---SET low column address
	OLED_Write_Byte(0x10,OLED_CMD);//---SET high column address
	OLED_Write_Byte(0x40,OLED_CMD);//--SET start line address  SET Mapping RAM Display Start Line (0x00~0x3F)
	OLED_Write_Byte(0x81,OLED_CMD);//--SET contrast control register
	OLED_Write_Byte(0xCF,OLED_CMD); // SET SEG Output Current Brightness
	OLED_Write_Byte(0xA1,OLED_CMD);//--SET SEG/Column Mapping     0xa0���ҷ��� 0xa1����
	OLED_Write_Byte(0xC8,OLED_CMD);//SET COM/Row Scan Direction   0xc0���·��� 0xc8����
	OLED_Write_Byte(0xA6,OLED_CMD);//--SET normal display
	OLED_Write_Byte(0xA8,OLED_CMD);//--SET multiplex ratio(1 to 64)
	OLED_Write_Byte(0x3f,OLED_CMD);//--1/64 duty
	OLED_Write_Byte(0xD3,OLED_CMD);//-SET display offSET	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_Write_Byte(0x00,OLED_CMD);//-not offSET
	OLED_Write_Byte(0xd5,OLED_CMD);//--SET display clock divide ratio/oscillator frequency
	OLED_Write_Byte(0x80,OLED_CMD);//--SET divide ratio, SET Clock as 100 Frames/Sec
	OLED_Write_Byte(0xD9,OLED_CMD);//--SET pre-charge period
	OLED_Write_Byte(0xF1,OLED_CMD);//SET Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_Write_Byte(0xDA,OLED_CMD);//--SET com pins hardware configuration
	OLED_Write_Byte(0x12,OLED_CMD);
	OLED_Write_Byte(0xDB,OLED_CMD);//--SET vcomh
	OLED_Write_Byte(0x40,OLED_CMD);//SET VCOM Deselect Level
	OLED_Write_Byte(0x20,OLED_CMD);//-SET Page Addressing Mode (0x00/0x01/0x02)
	OLED_Write_Byte(0x02,OLED_CMD);//
	OLED_Write_Byte(0x8D,OLED_CMD);//--SET Charge Pump enable/disable
	OLED_Write_Byte(0x14,OLED_CMD);//--SET(0x10) disable
	OLED_Write_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_Write_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_Write_Byte(0xAF,OLED_CMD);//--turn on oled panel
	OLED_Write_Byte(0xAF,OLED_CMD); /*display ON*/ 
	//OLED_Set_Contrast(0XFF);
	OLED_Clear();
	OLED_Set_PC(0,0); 	
}  


uint8 OLED_Reset(void)
{
	OLED_RST_SET;
	delay_ms(100);
	OLED_RST_CLR;
	delay_ms(100);
	OLED_RST_SET; 
	return 0;  //����0����ʾ��λ�ɹ�
}
/********************************************************************************************
*  �� �� ���� OLED_Write_Byte
*  ��    ��: ��OLED������һ�ֽ����ݻ�����
*  ���������uint8 dataҪ���͵����ݻ�����, uint8 cmd дOLED_CMDʱ�����дOLED_DATAʱ������
*  ��������� ��
*  �� �� ֵ:  ��
*  ��    ��:  ��ΰ
*  �������:  2018-08-10
*  ע������:  cmd����ֻ�����֣�OLED_CMD��OLED_DATAʱ
********************************************************************************************/
void OLED_Write_Byte(uint8 data,uint8 cmd)
{
	OLED_DC = cmd;
	OLED_CS_CLR;//����ʹ��Ƭѡ
	Spi_Write_Byte(data);
	OLED_CS_CLR;//�����ͷ�Ƭѡ
}	
void OLED_Clear(void)
{
	uint8 i,j;
	for(i=0;i<8;i++)
	{
		OLED_Write_Byte(0XB0+i,OLED_CMD);//����ҳ��ַ
		OLED_Write_Byte(0X02,OLED_CMD);//�����е�ַ����λ
		OLED_Write_Byte(0X10,OLED_CMD);//�����е�ַ����λ
		for(j=0;j<128;j++)
		{
			OLED_Write_Byte(0X00,OLED_DATA);//��Ļ��ʾ0�����һҳ
		}			
	}
}
void OLED_Set_PC(uint8 page,uint8 column)
{
	column +=2;//�Դ���132�У���Ļ��128�У���Ļ��0��127��Ӧ�Դ��2��129 
//	OLED_Write_Byte(0XB0+page,OLED_CMD);//����ҳ��ַ
//	OLED_Write_Byte(column&0X0F,OLED_CMD);//�����е�ַ����λ
//	OLED_Write_Byte((column>>4)|0X10,OLED_CMD);//�����е�ַ����λ
	
	OLED_Write_Byte(0xb0+page,OLED_CMD);
	OLED_Write_Byte(((column&0xf0)>>4)|0x10, OLED_CMD);
	OLED_Write_Byte((column&0x0f)|0x01,OLED_CMD); 
}
void OLED_Set_Pos(uint8 x,uint8 y)
{
	x +=2;//�Դ���132�У���Ļ��128�У���Ļ��0��127��Ӧ�Դ��2��129 
	OLED_Write_Byte(y&0X7F,OLED_CMD);//�����е�ַ
	OLED_Write_Byte(x&0X0F,OLED_CMD);//�����е�ַ����λ
	OLED_Write_Byte((x>>4)|0X10,OLED_CMD);//�����е�ַ����λ
}

void OLED_OFF(void)
{
	OLED_Write_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_Write_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_Write_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}
void OLED_ON(void)
{
	OLED_Write_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_Write_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_Write_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
void OLED_Set_Contrast(uint8 contrast)
{
	OLED_Write_Byte(0X81,OLED_CMD);//����Աȶ�����ģʽ
	OLED_Write_Byte(contrast,OLED_CMD);//���öԱȶ���ֵ0��255
}
/********************************************************************************************
*  �� �� ���� OLED_Show_Char
*  ��    ��:  OLED����ʾ�����ַ�
*  ���������uint8 pageҳ��ַ,uint8 column�е�ַ,char ch����ʾ�ַ�,
			 uint16 ch_size�ַ���С����ʽ��font.h��,uint8 mode��ʾģʽ��normal(������ʾ)��inverse(������ʾ)
*  ��������� ��
*  �� �� ֵ:  ��
*  ��    ��:  ��ΰ
*  �������:  2018-08-10
*  ע������:  ֻ����ʾ��ĸ�������ţ�������ʾ����
********************************************************************************************/
void OLED_Show_Char(uint8 page,uint8 column,char ch,uint16 ch_size,uint8 mode)
{
	uint8 i;
	uint8 ascii_offset = ch-' ';
	
	OLED_Set_PC(page,column);
	switch(ch_size)
	{
		case CH_SIZE1:
		{	
			for(i=0;i<6;i++)
			{
				if(mode)
				{
					OLED_Write_Byte(~F6X8[ascii_offset*6+i],OLED_DATA);
				}
				else
				{
					OLED_Write_Byte(F6X8[ascii_offset*6+i],OLED_DATA);
				}
			}
			
		}break;
		case CH_SIZE2:
		{	
			for(i=0;i<8;i++)
			{
				if(mode)
				{
					OLED_Write_Byte(~F8X16[ascii_offset*16+i],OLED_DATA);
				}
				else
				{
					OLED_Write_Byte(F8X16[ascii_offset*16+i],OLED_DATA);
				}
			}
			OLED_Set_PC(page+1,column);
			for(i=0;i<8;i++)
			{
				if(mode)
				{
					OLED_Write_Byte(~F8X16[ascii_offset*16+i+8],OLED_DATA);
				}
				else
				{
					OLED_Write_Byte(F8X16[ascii_offset*16+i+8],OLED_DATA);
				}
			}
		}break;
		case CH_SIZE3:
		{
			for(i=0;i<16;i++)
			{
				if(mode)
				{
					OLED_Write_Byte(~F16X24[ascii_offset*48+i],OLED_DATA);
				}
				else
				{
					OLED_Write_Byte(F16X24[ascii_offset*48+i],OLED_DATA);
				}
			}
			OLED_Set_PC(page+1,column);
			for(i=0;i<16;i++)
			{
				if(mode)
				{
					OLED_Write_Byte(~F16X24[ascii_offset*48+i+16],OLED_DATA);
				}
				else
				{
					OLED_Write_Byte(F16X24[ascii_offset*48+i+16],OLED_DATA);
				}
			}
			OLED_Set_PC(page+2,column);
			for(i=0;i<16;i++)
			{
				if(mode)
				{
					OLED_Write_Byte(~F16X24[ascii_offset*48+i+16*2],OLED_DATA);
				}
				else
				{
					OLED_Write_Byte(F16X24[ascii_offset*48+i+16*2],OLED_DATA);
				}
			}
		}break;
		default:break;
	}
}

/********************************************************************************************
*  �� �� ���� OLED_Show_String
*  ��    ��:  OLED����ʾ�ַ���
*  ���������uint8 pageҳ��ַ,uint8 column�е�ַchar *str����ʾ�ַ���,uint16 ch_size�ַ���С����ʽ��font.h��
			 uint8 mode��ʾģʽ��normal(������ʾ)��inverse(������ʾ)
*  ��������� ��
*  �� �� ֵ:  ��
*  ��    ��:  ��ΰ
*  �������:  2018-08-10
*  ע������:  ֻ����ʾ��ĸ�������ţ�������ʾ����
********************************************************************************************/
void OLED_Show_String(uint8 page,uint8 column,char *str,uint16 ch_size,uint8 mode)
{
	uint8 i = 0;
	while(*(str+i) != '\0')
	{
		OLED_Show_Char(page,column,*(str+i),ch_size,mode);
		switch(ch_size)
		{
			case CH_SIZE1:
			{
				column += 6;
				if(column>MAX_COLUMNC-1)
				{
					column = 0;
					page += 1; 
				}
			}break;
			case CH_SIZE2:
			{
				column += 8;
				if(column>MAX_COLUMNC-1)
				{
					column = 0;
					page += 2; 
				}
			}break;
			case CH_SIZE3:
			{
				column += 16;
				if(column>MAX_COLUMNC-1)
				{
					column = 0;
					page += 3; 
				}
			}break;
			default:break;
		}
		i++;
	}
}
/********************************************************************************************
*  �� �� ���� Number2String
*  ��    ��:  ����תΪ�ַ���
*  ���������	double num����,char *strת����ɴ����ַ�����
*  ��������� �������Զ�������λ
*  �� �� ֵ:  ��
*  ��    ��:  ��ΰ
*  �������:  2018-08-10
*  ע������:  ֻ����ʾ��ĸ�������ţ�������ʾ����
********************************************************************************************/
void Number2String(double num,char *str)
{//�����ж���������
	if(num-(int)num  < 0.00001)
	{//����
		sprintf(str,"%d",(int)num);
	}
	else
	{//�����ͣ�������λС��
		sprintf(str,"%.2f",num);
	}
}
void OLED_Show_Chinese(uint8 page,uint8 column,uint8 index,uint8 mode)
{
	uint8 i;
	OLED_Set_PC(page,column);
	for(i=0;i<16;i++)
	{
		if(mode)
		{
			OLED_Write_Byte(~HZ16X16[index*32+i],OLED_DATA);
		}
		else
		{
			OLED_Write_Byte(HZ16X16[index*32+i],OLED_DATA);
		}
		
	}
	OLED_Set_PC(page+1,column);
	for(i=0;i<16;i++)
	{
		if(mode)
		{
			OLED_Write_Byte(~HZ16X16[index*32+i+16],OLED_DATA);
		}
		else
		{
			OLED_Write_Byte(HZ16X16[index*32+i+16],OLED_DATA);
		}
	}
}
void OLED_Show_Multi_Chinese(uint8 page,uint8 column,uint8 index[],uint8 n,uint8 mode)
{
	uint8 i;
	for(i=0;i<n;i++)
	{
		OLED_Show_Chinese(page,column,index[i],mode);
		column +=16; 
	}
}
/********************************************************************************************
*  �� �� ���� OLED_Show_Pic
*  ��    ��:  OLED����ʾ
*  ��������� 
*  ��������� ��
*  �� �� ֵ:  ��
*  ��    ��:  ��ΰ
*  �������:  2018-08-10
*  ע������: 
********************************************************************************************/
void OLED_Show_Pic(uint8 x0,uint8 y0,uint8 x1,uint8 y1,uint8 BMP[],uint8 mode)
{ 	uint32 i=0;
	uint8 page0,column0;
	uint8 page1,column1;
	uint8 page,column;
	page0 = (x0+y0*128)/(8*128);
	column0 = x0;
	page1 = (x1+y1*128)/(8*128);
	column1 = x1;
	for(page=page0;page<=page1;page++)
	{
		OLED_Set_PC(page,column0);
		for(column=column0;column<=column1;column++)
		{     
			if(mode==normal)
			{
				OLED_Write_Byte(BMP[i++],OLED_DATA);	  
			}
			else
			{
				OLED_Write_Byte(~BMP[i++],OLED_DATA);	  
			}
			  	
		}
	}
}
void OLED_Show_Pic_t(uint8 x0,uint8 y0,uint8 x1,uint8 y1,uint8 BMP[],uint8 mode)//���޸�
{ 	uint32 i=0,n;
	uint8 page0,column0;
	uint8 page1,column1;
	uint8 page,column;
	page0 = (x0+y0*128)/(8*128);
	column0 = x0;
	page1 = (x1+y1*128)/(8*128);
	column1 = x1;
	for(page=page0;page<=page1;page++)
	{
		OLED_Set_PC(page,column0);
		for(column=column0;column<=column1;column++)
		{     
			if(mode==normal)
			{
				OLED_Write_Byte(BMP[i++],OLED_DATA);	  
			}
			else
			{
				n = y1-page*8;
				if(n<7)
				{
					OLED_Write_Byte((~BMP[i++])&(0XFF<<(8-n)),OLED_DATA);	
				}
				else
					OLED_Write_Byte(~BMP[i++],OLED_DATA);	  
			}
			  	
		}
	}
}
