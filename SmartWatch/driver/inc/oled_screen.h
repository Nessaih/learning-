#ifndef __OLED_SCREEN_H__
#define __OLED_SCREEN_H__

#include "stm32f4xx.h"
#include "sys.h"
#include "type.h"
#include "spi.h"
#include "delay.h"

#define normal		0//������ʾ
#define inverse		1//������ʾ

#define MAX_COLUMNC	128

#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

//OLED_DC  PA15
#define OLED_DC		PAout(15)//1��ʾ��OLED�����ݣ�0��ʾ��OLED������

//OLED_CS  PB7	
#define OLED_CS_SET		PBout(7) = 1  	//Ƭѡ��ֹ
#define OLED_CS_CLR		PBout(7) = 0	//Ƭѡʹ��

//OLED_RES  PB13
#define OLED_RST_SET	PBout(13) = 1  	//����λ
#define OLED_RST_CLR	PBout(13) = 0	//���͸�λ

/*�ַ������С���߰�λ���ֿ��Ͱ�λ���ָ�
�磺F8X16[]��ʾһ���ַ�ռ8�У�16�У��������СΪ0X0810*/
#define CH_SIZE1   0X0608
#define CH_SIZE2   0X0810
#define CH_SIZE3   0X1018

extern void OLED_Io_Init(void);
extern void OLED_Init(void);
extern uint8 OLED_Reset(void);
extern void OLED_Write_Byte(uint8 data,uint8 cmd);
extern void OLED_Clear(void);
extern void OLED_Set_PC(uint8 page,uint8 column);
extern void OLED_Set_Pos(uint8 x,uint8 y);
extern void OLED_OFF(void);
extern void OLED_ON(void);
extern void OLED_Set_Contrast(uint8 contrast);
extern void OLED_Show_Char(uint8 page,uint8 column,char ch,uint16 ch_size,uint8 mode);
extern void OLED_Show_String(uint8 page,uint8 column,char *str,uint16 ch_size,uint8 mode);
extern void Number2String(double num,char *str);
extern void OLED_Show_Chinese(uint8 page,uint8 column,uint8 index,uint8 mode);
extern void OLED_Show_Multi_Chinese(uint8 page,uint8 column,uint8 index[],uint8 n,uint8 mode);
extern void OLED_Show_Pic(uint8 x0,uint8 y0,uint8 x1,uint8 y1,uint8 BMP[],uint8 mode);
void OLED_Show_Pic_t(uint8 x0,uint8 y0,uint8 x1,uint8 y1,uint8 BMP[],uint8 mode);
#endif

