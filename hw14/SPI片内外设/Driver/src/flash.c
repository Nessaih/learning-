#include "flash.h"

/********************************************************************************************
*  �� �� ���� Flash_Io_Init
*  ��    ��:  Flash���ƶ˿ڳ�ʼ�����ã�CSƬѡ�����������
*  ��������� ��   
*  ��������� ��
*  �� �� ֵ:  ��
*  ��    ��:  ��ΰ
*  �������:  2018-07-31
*  ע������:  ��
********************************************************************************************/
void Flash_Io_Init(void)
{
	//PB14---CS��
	RCC->AHB1ENR |=0x01<<1;
	GPIOB->MODER &=~ (0x03<<28);
	GPIOB->MODER |=0x01<<28;
	GPIOB->OTYPER &=~(0x01<<14);
	GPIOB->PUPDR &=~(0x03<<28);
	GPIOB->OSPEEDR	&=~(0x03<<28);
	//GPIOB->OSPEEDR |=(0x02<<28);
	FLASH_CS_OH;
}
/********************************************************************************************
*  �� �� ���� Flash_Init
*  ��    ��:  Flash��ʼ����SPI���߶˿ں�flashƬѡ�˿�
*  ��������� ��   
*  ��������� ��
*  �� �� ֵ:  ��
*  ��    ��:  ��ΰ
*  �������:  2018-07-31
*  ע������:  ��
********************************************************************************************/


#if Simulation
/***********ʹ��IO��ģ��****************/
void Flash_Init(void)
{
	Spi_Io_Init();
	Flash_Io_Init();
}

/********************************************************************************************
*  �� �� ���� Flash_RW_Byte
*  ��    ��:  Flash��ȡд�뺯��
*  ��������� һ�ֽڴ�д������   
*  ��������� ��
*  �� �� ֵ:  ��ȡ��һ�ֽ�����
*  ��    ��:  ��ΰ
*  �������:  2018-07-31
*  ע������:  ��
********************************************************************************************/


uint8 Flash_RW_Byte(uint8 data)
{
	return Spi_RW(data);
}

#else
/***********************************************ʹ��Ƭ������****************************************************/
/***********************************************ʹ��Ƭ������****************************************************/
/***********************************************ʹ��Ƭ������****************************************************/

void Flash_Init(void)
{
	
	//SPI--I0��ʼ��
	RCC->AHB1ENR |= 0X01;//PB
	GPIOB->MODER &=~ ((0X03<<6)|(0X03<<8)|(0X03<<10));
	GPIOB->MODER |= ((0X02<<6)|(0X02<<8)|(0X02<<10));//���ù���
	GPIOB->OSPEEDR &=~ ((0X03<<6)|(0X03<<10));
	GPIOB->OSPEEDR |= ((0X02<<6)|(0X02<<10));//����ٶ�50Mhz
	GPIOB->PUPDR &=~ ((0X03<<6)|(0X03<<8)|(0X03<<10));//����
	 GPIOB->OTYPER &= ~((0X01<<3)|(0X01<<5));
	GPIOB->AFR[0] &=~ ((0X0F<<12)|(0X0F<<20)|(0X0F<<16));
	GPIOB->AFR[0] |= ((0X05<<12)|(0X05<<20)|(0X05<<16));//ѡ��spi1���ù���
	Flash_Io_Init();
	
	//SPI1�Ĵ�������
	RCC->APB2ENR |= 0X01<<12;
	SPI1->CR1 &=~ ((0x01<<15)|(0x01<<11)|(0x01<<10)|(0X01<<7));//˫�ߵ���ģʽ;����֡��λ;�ȷ���λ	
	SPI1->CR1 |= ((0X01<<9)|(0X01<<8)|((0X01<<2)));//�����������ģʽ;��ģʽ;������
	SPI1->CR1 &=~ (0X07<<3);//������42M
	SPI1->CR1 &=~ (0X03<<0);//ʱ�Ӽ��ԣ���λѡ��ģʽ0
	SPI1->CR2  &=~ (0X01<<4);//SPI Motorolaģʽ
	SPI1->I2SCFGR  &=~(0X01<<11);//ѡ��SPIģʽ
	SPI1->CR1|= 0X01<<6;//SPI ʹ��
}

uint8 Flash_RW_Byte(uint8 data)
{
	while(!(SPI1->SR&(0X01<<1)));
	SPI1->DR = data;
	while(!(SPI1->SR&(0X01<<0)));
	data =SPI1->DR ;
	return data;
}
#endif



/********************************************************************************************
*  �� �� ���� Flash_Write_Addr
*  ��    ��:  Flashд��24λ��ַ
*  ��������� 24λ��ַ   
*  ��������� ��
*  �� �� ֵ:  ��
*  ��    ��:  ��ΰ
*  �������:  2018-07-31
*  ע������:  ��
********************************************************************************************/
void Flash_Write_Addr(uint32 Addr)
{
	uint8 *temp = (uint8 *)&Addr;
	int8 i;
	for(i=2;i>=0;i--)
	{
		Flash_RW_Byte(*(temp+i));
	}
}
/*******************************************************************************************
*******************************����ΪFLASH����**********************************************
********************************************************************************************/


/********************************************************************************************
*  �� �� ���� Flash_CMD_Read_ID
*  ��    ��:  Flash��ȡ16λID,����ȡֵΪOXEF16��˵��Flash��������
*  ��������� ��   
*  ��������� ��
*  �� �� ֵ:  ��
*  ��    ��:  ��ΰ
*  �������:  2018-07-31
*  ע������:  ��
********************************************************************************************/
void Flash_CMD_Read_ID(void)
{
	uint16 temp = 0;
	FLASH_CS_OL;//CS��Ч��ѡ��Flash������Flash����MCUͨѶ
	Flash_RW_Byte(FLASH_CMD_DEVICE_ID);
	Flash_Write_Addr(0x00);
	temp = Flash_RW_Byte(DUMMY_BYTE)<<8;
	temp |= Flash_RW_Byte(DUMMY_BYTE);
	FLASH_CS_OH;//CS��Ч���ͷ�Flash������Flash������MCUͨѶ
	printf("ID:0X%X\r\n",temp);
}

void Flash_CMD_Write_Enable(void)
{
	FLASH_CS_OL;//CS��Ч��ѡ��Flash������Flash����MCUͨѶ
	Flash_RW_Byte(FLASH_CMD_WRITE_ENABLE);
	FLASH_CS_OH;//CS��Ч���ͷ�Flash������Flash������MCUͨѶ
}
void Flash_CMD_Write_Disable(void)
{
	FLASH_CS_OL;//CS��Ч��ѡ��Flash������Flash����MCUͨѶ
	Flash_RW_Byte(FLASH_CMD_WRITE_DISABLE);
	FLASH_CS_OH;//CS��Ч���ͷ�Flash������Flash������MCUͨѶ
}
uint8 Flash_Read_Status_Reg1(void)
{
	uint8 Status_Reg1;
	FLASH_CS_OL;
	Flash_RW_Byte(FLASH_CMD_READ_STATUS_REG1);
	Status_Reg1 = Flash_RW_Byte(DUMMY_BYTE);
	FLASH_CS_OH;
	return Status_Reg1;
}
uint8 Flash_Read_Status_Reg2(void)
{
	uint8 Status_Reg2;
	FLASH_CS_OL;
	Flash_RW_Byte(FLASH_CMD_READ_STATUS_REG2);
	Status_Reg2 = Flash_RW_Byte(DUMMY_BYTE);
	FLASH_CS_OH;
	return Status_Reg2;
}
uint8 Flash_Write_Status_Reg(uint16 Reg_value)
{
	Flash_CMD_Write_Enable();
	FLASH_CS_OL;
	Flash_RW_Byte(FLASH_CMD_WRITE_STATUS_REG);
	Flash_RW_Byte(Reg_value);
	Flash_RW_Byte((Reg_value>>8)&0X03);
	FLASH_CS_OH;
	return Flash_Wait_Busy(FLASH_WRITE_STATUS_REG_TIME_OUT);
}
uint8 Flash_Wait_Busy(uint16 Time_Out)
{
	uint16 delay = Time_Out;
	uint8 status_reg1 = 0;
	do{
		status_reg1 = Flash_Read_Status_Reg1();
		delay_ms(1);
		delay--;
	}while((status_reg1&0X01)&&delay);
	if(delay)
	{
		return 0;
	}
	return 1;	
}
/********************************************************************************************
*  �� �� ���� Flash_Sector_Erase
*  ��    ��:  Flash������������
*  ��������� uint32 ADDR������ַ������Ҫ�������׵�ַ���õ�ַ�����ĸ�����������ĸ�����
*  ��������� ��
*  �� �� ֵ:  ����0��ʾ��������������1��ʾ�쳣
*  ��    ��:  ��ΰ
*  �������:  2018-07-31
*  ע������:  ��
********************************************************************************************/
uint8 Flash_Sector_Erase(uint32 ADDR)
{
	Flash_CMD_Write_Enable();
	FLASH_CS_OL;
	Flash_RW_Byte(FLASH_CMD_SECTOR_ERASE);
	Flash_Write_Addr(ADDR);
	FLASH_CS_OH;
	return Flash_Wait_Busy(FLASH_SECTOR_ERASE_TIME_OUT);
}
/********************************************************************************************
*  �� �� ���� Flash_Sector_Erase
*  ��    ��:  Flash�������������
*  ��������� uint32 ADDR������ַ������Ҫ�������׵�ַ���õ�ַ�����ĸ�����������ĸ�����
			  uint16 num��������������num<=2048��������ADDR�����������Լ�������ڵ�num-1������
*  ��������� ��
*  �� �� ֵ:  ����0��ʾ��������������1��ʾ�쳣
*  ��    ��:  ��ΰ
*  �������:  2018-07-31
*  ע������:  ��
********************************************************************************************/
void Flash_NSector_Erase(uint32 ADDR,uint16 num)
{
	uint16 i;
	for(i = 0;i < num;i ++)
	{
		Flash_Sector_Erase(ADDR+(i*FLASH_SECTOR_SIZE));
	}
}
/********************************************************************************************
*  �� �� ���� Flash_Write_Page
*  ��    ��:  Flashд������(��������������ҳ)
*  ��������� uint8 *dataд�������, uint32 nbyte���鳤��, uint32 ADDRд�����ʼ��ַ
*  ��������� ��
*  �� �� ֵ:  ��
*  ��    ��:  ��ΰ
*  �������:  2018-07-31
*  ע������:  ��
********************************************************************************************/
void Flash_Write_Single_Page(uint8 *data, uint16 nbyte, uint32 ADDR)
{
	uint16 i,len;	
	len = FLASH_CALCULATE_PAGE_1ST_ADDR(ADDR) + FLASH_PAGE_SIZE - ADDR;
	if(nbyte < len)
	{
		len = nbyte;
	}
	Flash_CMD_Write_Enable();
	FLASH_CS_OL;
	Flash_RW_Byte(FLASH_CMD_WRITE_DATA);//д����
	Flash_Write_Addr(ADDR);				//д��ַ
	for(i = 0;i<len;i++)
	{
		Flash_RW_Byte(*(data+i));		//д����
	}
	FLASH_CS_OH;
	Flash_Wait_Busy(FLASH_PEGE_PROGARM_TIME_OUT);
}
/********************************************************************************************
*  �� �� ���� Flash_Write_Data
*  ��    ��:  Flashд������(�����������ɿ�ҳ)
*  ��������� uint8 *dataд�������, uint32 nbyte���鳤��, uint32 ADDRд�����ʼ��ַ
*  ��������� ��
*  �� �� ֵ:  ��
*  ��    ��:  ��ΰ
*  �������:  2018-07-31
*  ע������:  ��
********************************************************************************************/
void Flash_Write_Cross_Page(uint8 *data, uint32 nbyte, uint32 ADDR)
{
	uint16 i,len;	
	while(nbyte)
	{
		len = FLASH_CALCULATE_PAGE_1ST_ADDR(ADDR) + FLASH_PAGE_SIZE - ADDR;
		if(nbyte < len)
		{
			len = nbyte;
		}
		Flash_CMD_Write_Enable();
		FLASH_CS_OL;
		Flash_RW_Byte(FLASH_CMD_WRITE_DATA);//д����
		Flash_Write_Addr(ADDR);				//д��ַ
		for(i = 0;i<len;i++)
		{
			Flash_RW_Byte(*(data+i));		//д����
			//printf("%d ",*(data+i));
		}
		FLASH_CS_OH;
		Flash_Wait_Busy(FLASH_PEGE_PROGARM_TIME_OUT);
		ADDR += len;
		data += len;
		nbyte -=len; 	
	}
	FLASH_CS_OH;
	//printf("д����ִ�����\n");
}
/********************************************************************************************
*  �� �� ���� Flash_Read_Data
*  ��    ��:  Flash��ȡ����
*  ��������� uint8 *data��ȡ���ݴ洢������, uint32 nbyte���鳤��, uint32 ADDR��ȡ����ʼ��ַ
*  ��������� ��
*  �� �� ֵ:  ��
*  ��    ��:  ��ΰ
*  �������:  2018-07-31
*  ע������:  ��
********************************************************************************************/
void Flash_Read_Data(uint8 *data, uint32 nbyte, uint32 ADDR)
{
	uint32 i;
	FLASH_CS_OL;
	Flash_RW_Byte(FLASH_CMD_READ_DATA);
	Flash_Write_Addr(ADDR);
	for(i = 0;i<nbyte;i++)
	{
		*(data+i) = Flash_RW_Byte(DUMMY_BYTE);
	}
	FLASH_CS_OH;
	//printf("������ִ�����\n");
}


/********************************************************************************************
*  �� �� ���� Flash_Copy_Sector
*  ��    ��:  ��������
*  ��������� 
*  ��������� ��
*  �� �� ֵ:  ��
*  ��    ��:  ��ΰ
*  �������:  2018-08-1
*  ע������:  ��
********************************************************************************************/
void Flash_Copy_Sector(uint32 ADDR_Src,uint32 ADDR_Dst)
{
	uint8 i;
	uint8 data_buff[FLASH_PAGE_SIZE];
	ADDR_Src = FLASH_CALCULATE_SECTOR_1ST_ADDR(ADDR_Src);
	ADDR_Dst = FLASH_CALCULATE_SECTOR_1ST_ADDR(ADDR_Dst);
	for(i=0;i<FLASH_PAGE_NUM_OF_EACH_SECTOR;i++)
	{
		Flash_Read_Data(data_buff,FLASH_PAGE_SIZE,ADDR_Src);
		Flash_Write_Single_Page(data_buff,FLASH_PAGE_SIZE,ADDR_Dst);
		ADDR_Src += FLASH_PAGE_SIZE;
		ADDR_Dst += FLASH_PAGE_SIZE;
	}
}
/********************************************************************************************
*  �� �� ���� Flash_Copy_Date
*  ��    ��:  �����ַ����
   ˼    ·����1�����ȼ���Ŀ���ַ����ҳ��ʣ��洢�ֽ���len
			 ��2����ȡԴ��ַlen���ֽ����ݣ�д��Ŀ���ַ
			 ��3��Դ��ַ���£�ADDR_Src+=len����
				  Ŀ���ַ���£�ADDR_Dst+=len����
				  �����ֽ������£�nbyte-=len����
*  ��������� uint32 ADDR_SrcԴ��ַ,uint32 ADDR_DstĿ���ַ,uint32 nbyte�����ֽ���
*  ��������� ��
*  �� �� ֵ:  ��
*  ��    ��:  ��ΰ
*  �������:  2018-08-1
*  ע������:  ��
********************************************************************************************/
void Flash_Copy_Date(uint32 ADDR_Src,uint32 ADDR_Dst,uint32 nbyte)
{
	uint16 len;
	uint8 data_buff[FLASH_PAGE_SIZE];
	while(nbyte)
	{
		len = FLASH_CALCULATE_PAGE_1ST_ADDR(ADDR_Dst) + FLASH_PAGE_SIZE - ADDR_Dst;
		if(nbyte < len)
		{
			len = nbyte;
		}
		Flash_Read_Data(data_buff,len,ADDR_Src);
		Flash_Write_Single_Page(data_buff,len,ADDR_Dst);
		ADDR_Src += len;
		ADDR_Dst += len;
		nbyte -= len;
	}
}
/********************************************************************************************
*  �� �� ���� Flash_Write_Sector
*  ��    ��:  дһ��������������,������
   ˼    ·�� ��1���͵�ҳд���ƣ��ȼ����������ʣlen���ֽ�
			  ��2�����Ҫд���ֽ���nbyteС��len��д��nbyte���ֽ�
			  ��3�����Ҫд���ֽ���nbyte����len��д��len���ֽ�
*  ��������� 
*  ��������� ��
*  �� �� ֵ:  ��
*  ��    ��:  ��ΰ
*  �������:  2018-08-1
*  ע������:  ��
********************************************************************************************/
void Flash_Write_Single_Sector(uint8 *data, uint32 nbyte, uint32 ADDR)
{
	uint32 ADDR_Backup = FLASH_BACKUP_SECTOR;
	uint16 offset = FLASH_CALCULATE_SECTOR_ADDR_OFFSET(ADDR);
	uint16 len = FLASH_CALCULATE_SECTOR_1ST_ADDR(ADDR) + FLASH_SECTOR_SIZE - ADDR;//����ʣ��ռ�
	if(nbyte<len)
	{/*д���ֽ������ܳ�������ʣ��ռ䣬����������ֻд��ʣ��ռ�*/
		len = nbyte;
	}
	if(0==offset)//д���ֽڵ�ַ��λ��������
	{
		Flash_Sector_Erase(ADDR);//����ԭ����
		Flash_Write_Cross_Page(data,len,ADDR);
	}
	else if((offset+len-1)==FLASH_SECTOR_SIZE)//д���ֽڵ�ַ��λ������β
	{
		Flash_Sector_Erase(ADDR_Backup);//������������
		Flash_Copy_Sector(ADDR,ADDR_Backup);//����ԭ��������
		Flash_Sector_Erase(ADDR);//����ԭ����
		Flash_Copy_Date(ADDR_Backup,FLASH_CALCULATE_SECTOR_1ST_ADDR(ADDR),offset-1);
		Flash_Write_Cross_Page(data,len,ADDR);
	}
	else//д���ֽڵ�ַ��λ�������м�
	{
		Flash_Sector_Erase(ADDR_Backup);//������������
		Flash_Copy_Sector(ADDR,ADDR_Backup);//����ԭ��������
		Flash_Sector_Erase(ADDR);//����ԭ����
		Flash_Copy_Date(ADDR_Backup,FLASH_CALCULATE_SECTOR_1ST_ADDR(ADDR),offset-1);
		Flash_Write_Cross_Page(data,len,ADDR);
		Flash_Copy_Date(ADDR_Backup+offset+len,ADDR+len,FLASH_SECTOR_SIZE-offset-len+1);
	}
	//printf("��������д����ִ�����\n");
}
/********************************************************************************************
*  �� �� ���� Flash_Write_Sector
*  ��    ��:  дһ��������������,������
*  ��������� 
*  ��������� ��
*  �� �� ֵ:  ��
*  ��    ��:  ��ΰ
*  �������:  2018-08-1
*  ע������:  ��
********************************************************************************************/
void Flash_Write_Cross_Sector(uint8 *data, uint32 nbyte, uint32 ADDR)
{
	uint16 len;	
	while(nbyte)
	{
		len = FLASH_CALCULATE_SECTOR_1ST_ADDR(ADDR) + FLASH_SECTOR_SIZE - ADDR;//����ʣ��ռ�
		if(nbyte < len)
		{
			len = nbyte;
		}
		Flash_Write_Single_Sector(data,len,ADDR);
		ADDR += len;
		data += len;
		nbyte -=len; 	
	}
	delay_ms(7);
	//printf("������д����ִ�����\n");
}
