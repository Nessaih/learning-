#include "iic.h"
void IIC_IO_Init(void)
{
	  /*****IIC_SCL����Ϊ��©���****/
	RCC->AHB1ENR |= 1<<1;//ʹ��PBʱ��
	GPIOB->MODER &=~(3<<16);//����
	GPIOB->MODER |= 1<<16;//GPIOB8����ͨ�����ģʽ
	GPIOB->OTYPER |= 1<<8;//GPIOB8����Ϊ��©ģʽ
	/****IIC_SDA����Ϊ��©���****/
	GPIOB->MODER &=~(3<<18);//����
	GPIOB->MODER |= 1<<18;//GPIOB9������ͨģʽ
	GPIOB->OTYPER |= 1<<9;//GPIOB9����Ϊͨ�����ģʽ
	IIC_SDA_OH;
	IIC_SCL_OH;
}
void IIC_Start(void)
{
	delay_us(5);
  IIC_SCL_OH;
  IIC_SDA_OH;
  delay_us(5);//��ʱ5us
  IIC_SDA_OL;
  delay_us(5);//��ʱ5us
  IIC_SCL_OL;
}
void IIC_Stop(void)
{
	IIC_SDA_OL;
  delay_us(5);
  IIC_SCL_OH;
  delay_us(5);//��ʱ5us
  IIC_SDA_OH;
  delay_us(5);//��ʱ5us
}
//data �������͵�����
//����ֵ��0��ʾӦ��1��ʾ��Ӧ��
u8 IIC_WriteByte(u8 data)
{
  u8 i;
  u8 ack = 2;
  for(i=0;i<8;i++)  //8��ʱ�Ӵ���8λ���ݣ������λ��ʼ����
  {
    if(data &(1<<(7-i)))  
    {
      IIC_SDA_OH;
    }
    else
    {
      IIC_SDA_OL;
    }
    delay_us(5);//��ʱ5us
    IIC_SCL_OH; 
    delay_us(5);//��ʱ5us
    IIC_SCL_OL;
  }
  IIC_SDA_OH;//SDA����ߵ͵�ƽ�л�Ϊ����
  delay_us(5);//��ʱ5us
  IIC_SCL_OH;
  if(IIC_SDA_READ)//SDA����ĵ�ƽΪ�ߵ�ƽ��ʾ��Ӧ��
  {
    ack = 1;
  }
  else  //SDA����ĵ�ƽΪ�͵�ƽ��ʾӦ��
  {
    ack = 0;
  }
  delay_us(5);//��ʱ5us
  IIC_SCL_OL;
  return ack;
}

//����ֵ��ʾ��ȡ��������
//�β�ack����ʾ��ȡһ���ֽ����ݺ������Ӧ��0��Ӧ��1����Ӧ��
u8  IIC_ReadByte(u8 ack)
{
  u8 i;
  u8 data = 0;
  IIC_SDA_OH;//SDA����ߵ�ƽ���л�Ϊ����
  for(i=0;i<8;i++)  //����8��ʱ�ӣ���ȡ8λ����
  {
    delay_us(5);//��ʱ5us
    IIC_SCL_OH;
    data = data <<1;
    if(IIC_SDA_READ)
    {
      data |= 1<<0;
    }
    else   //SDA����ĵ͵�ƽ��ƽ
    {
      data &=~(1<<0);
    }	
    delay_us(5); //��ʱ5us
    IIC_SCL_OL;		
  }
  //�����ھŸ�ʱ�ӣ�����Ӧ���źš�
  if(ack == 0)
  {
    IIC_SDA_OL;   
  }
  else
  {
    IIC_SDA_OH;
  }
  delay_us(5);//��ʱ5us
  IIC_SCL_OH;
  delay_us(5);//��ʱ5us
  IIC_SCL_OL;
  return data;
}