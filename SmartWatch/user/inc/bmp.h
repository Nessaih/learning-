//////////////////////////////////////////////////////////////////////////////////	 
//
//
//存储图片数据，图片大小为64*32像素
//
/////////////////////////////////////////////////////////////////////////////////

#ifndef __BMP_H
#define __BMP_H
const unsigned char BMP1[] =
{
0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x3F,0x1F,0x1F,0x0F,0x0F,0x07,0x07,0x07,0x07,0x07,0x07,0x0F,0x0F,0x0F,0x1F,0x1F,0x3F,0x7F,0xFF,0xFF,0x7F,0x3F,0x3F,0x1F,0x0F,0x0F,0x0F,0x07,0x07,0x07,
0x07,0x07,0x07,0x0F,0x0F,0x0F,0x1F,0x3F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x0F,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,
0x38,0x18,0x70,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x07,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xC0,0x70,0x18,0x08,0xF8,0xC0,0x00,0xF0,0x7F,0x03,0xE0,0xFC,0xE0,0x07,0x7E,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xC0,0xFF,0xFF,0xFF,0xFF,0xE7,0xF7,0xE4,0xE4,0xE4,0x34,0x24,0x34,0x26,0x27,0x11,0x08,0x0F,0xF8,0x00,0x3F,0xFE,0x07,0xE0,0x7E,0x07,0x00,0x07,0x1E,0x30,0x27,0x26,0x34,
0x24,0x24,0x24,0x66,0x43,0xC1,0xC1,0x43,0x62,0x3C,0x00,0x00,0x00,0x80,0xE0,0xF8,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xF8,0xF0,0xE0,0xC0,0x80,0x00,0x0F,
0x3E,0x60,0x60,0x3C,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFE,0xFC,0xF8,0xF0,0xF0,0xE0,0xC0,0xC0,0x80,0x80,0xC0,0xC0,0xE0,0xF0,0xF0,0xF8,0xFC,0xFC,0xFE,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,/*"G:\项目\1.可穿戴设备\图片资料\心率1 - 副本.bmp",0*/
/* (50 X 50 )*/
};
const unsigned char Pulse_bmp[] =
{
0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xE0,0xF0,0xF0,0xF8,0xF8,0xFC,0xFC,0xFC,0xF8,0xF8,0xF8,0xF0,0xF0,0xE0,0xE0,0xC0,0xC0,0x80,0x00,0x00,0x80,0xC0,0xC0,0xE0,0xE0,0xF0,0xF0,0xF8,
0xFC,0xFC,0xFE,0xFE,0xFE,0xFE,0xFC,0xF8,0xF0,0xE0,0xE0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xF0,0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0xFF,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xF8,0xE0,0x80,
0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0x03,0x03,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0x07,0x00,0x80,0x00,0x07,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0x03,0x07,0x07,0x07,0xC7,0xC7,0xC7,0xC7,0xC7,0xC7,0xC7,0xC7,0xC1,0xC0,0xF0,0xE0,0x80,0x01,
0x0F,0x3F,0x1F,0x03,0x80,0xF8,0xFF,0xFF,0xFF,0xF8,0xE0,0x01,0x07,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x0F,0x07,0x07,0x0F,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x1F,0x03,0x00,
0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x0F,0x1F,0x3F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xE0,0xC0,0xE0,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFE,0xFC,0x7C,0x3E,0x1F,0x0F,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x0F,0x1F,
0x3F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x3F,0x1F,0x0F,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x0F,0x1F,0x3F,0x3F,0x1F,0x0F,0x07,0x03,0x01,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"G:\项目\1.可穿戴设备\UI\ui_icon\心率，修改后.BMP",0*/
/* (54 X 54 )*/

};
const unsigned char BP_bmp[] =
{
	
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xE0,0xF8,0xFC,0xFE,0xFF,0x3F,
0x1F,0x07,0x07,0x07,0x07,0x0F,0x1F,0xFF,0xFF,0xFE,0xFC,0xF0,0x00,0x00,0x00,0xC0,0xF0,0xF8,0xF8,0xF8,0xF8,0xF8,0xF0,0xF0,0xE0,0xE0,0xC0,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xC0,0xC0,0xE0,0xE0,0xF0,0xFC,0xFE,0xFF,0x7F,0x1F,0x0F,0x03,0x00,0x00,0x00,0x00,0x80,0xC0,0xF8,0xFC,0xFF,0xFF,0x7F,0x1F,0x87,0xE3,0xF0,0xFC,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFE,0xFC,0x38,0x00,0x00,0x78,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0x1F,0x00,0x00,0x00,0xC0,0xF0,
0xF8,0xFE,0xFF,0x7F,0x1F,0x0F,0xC3,0xF1,0xF8,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x9F,0x07,0x03,0x00,0x00,0x00,
0x00,0x00,0x00,0x01,0x03,0x03,0x03,0x03,0x03,0x01,0x00,0x00,0xE0,0xF8,0xFC,0xFF,0xFF,0x3F,0x1F,0x07,0x01,0x38,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0x07,0x03,0x01,0x61,0xF0,0xF0,0xE0,0x01,0x01,0x03,0x0F,0xFF,0xFF,0xFC,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x1F,0x3F,0x7F,0xFF,0xFC,
0xF8,0xF8,0xF0,0xF0,0xF8,0xFC,0xFF,0x7F,0x3F,0x0F,0x07,0x0F,0x0F,0x1F,0x1F,0x3F,0x7F,0x7F,0x7F,0x7E,0x78,0x78,0xF8,0xF0,0xF1,0xF7,0xFE,0x78,0x7C,0x3F,0x1F,0x0F,0x07,0x01,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"G:\项目\1.可穿戴设备\UI\ui_icon\血压.bmp",0*/
/* (54 X 54 )*/
};
const unsigned char step_bmp[] =
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0xE0,0x60,0xF8,0xF8,0x9C,0xF8,0xFE,0xCE,0xC6,0xFE,0xFC,0xFE,0x8F,0x83,0xE7,0xFE,0x7C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x0D,0x9F,0xCF,0xE6,0x73,0x3B,0x19,0x1D,0x1C,0x0D,
0x0D,0x0C,0x0C,0x0D,0x1D,0xF9,0xF9,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xE0,0xC0,0x80,0x80,0xC0,0xC0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0xF0,0x38,0x1C,0x0E,0x07,0x03,0x00,0x00,0x00,0x00,0x1F,0x3F,0x70,0x70,0xFF,0x9F,0x9F,
0xBF,0xB0,0xBF,0x9F,0x1E,0x33,0x7F,0xCC,0xFC,0xF8,0x60,0xE0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x1F,0xFE,0xF0,0x80,0x00,0x00,0x00,
0x0F,0x3F,0x78,0xE0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0xFF,0xFF,0x83,0x01,0x01,0x01,0x01,0x03,0x03,0x03,0x07,0x06,0x1E,0x7D,0xFB,0xE3,0x01,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x3F,0x7F,0xE0,0xC0,0xC0,0xC0,0xC0,0xC0,0xF1,0x7F,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x9E,
0xFC,0xF8,0x00,0x00,0x00,0x00,0x00,0xC0,0xFC,0x7F,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,
0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xF8,0x1E,0x0F,0x03,0x01,0x00,0x00,0x00,0xF8,0xFF,0x0F,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x1F,0x38,0x38,
0x30,0x30,0x30,0x38,0x1E,0x0F,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"G:\项目\1.可穿戴设备\UI\ui_icon\right_footprint.bmp",0*/
/* (54 X 54 )*/
};
const unsigned char CalDist[] =
{
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0xF0,0xF0,0x60,0x60,0xE0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0xF8,0x70,0xE0,0xE0,0xC0,
	0x80,0xC0,0xFF,0xFF,0x00,0x00,0x01,0x03,0x0F,0x3E,0x7C,0xF0,0xE0,0xFF,0x0F,0x06,0x0C,0xF8,0xF0,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x80,0xC0,0xE0,0x70,0x38,0x1C,0x0E,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xFF,0xF0,0x80,0x00,0x00,0x00,0x01,0x03,0x01,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0x70,0x38,0x1C,0x0E,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x0F,0x1F,0x7E,0xFC,0xE0,0xE0,0xC0,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xC0,0xC0,0xF0,
	0xFE,0x7F,0x3F,0x1F,0x80,0xC0,0xE0,0x70,0x38,0x1C,0x0E,0x07,0x03,0x01,0x00,0x00,0xC0,0xE0,0xF0,0xF0,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF0,0xE0,0xC0,0x80,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x83,0xC3,0xE3,0x71,0x38,0x1C,0x0E,0x07,0x03,0x01,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xF8,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x1F,0x0F,0x07,0x07,0x07,0x07,0x07,0x07,0x0F,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xF8,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0x70,0x38,0x1C,0x0E,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x0F,0x1F,
	0x3F,0x7F,0xFF,0xFF,0xFF,0xFC,0xF8,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF8,0xFC,0xFF,0xFF,0xFF,0xFF,0x7F,0x3F,0x0F,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x70,0x38,0x1C,0x0E,0x07,
	0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x0F,0x1F,
	0x3F,0x7F,0xFF,0x7F,0x3F,0x1F,0x0F,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"G:\项目\1.可穿戴设备\UI\ui_icon\222222.bmp",0*/
	/* (64 X 64 )*/

};

//OLED_drawBMP(100,0,124,2,(u8*)Battery100);
	
const unsigned char Battery100[] =
{
0xF8,0x08,0xE8,0xE8,0xE8,0xE8,0x08,0xE8,0xE8,0xE8,0xE8,0x08,0xE8,0xE8,0xE8,0xE8,0x08,0xE8,0xE8,0xE8,0xE8,0x08,0xF8,0xE0,0x3F,0x20,0x2F,0x2F,0x2F,0x2F,0x20,0x2F,0x2F,0x2F,0x2F,0x20,
0x2F,0x2F,0x2F,0x2F,0x20,0x2F,0x2F,0x2F,0x2F,0x20,0x3F,0x0F/*"G:\项目\1.可穿戴设备\UI\ui_icon\7.bmp",0*/
/* (24 X 16 )*/
};
const unsigned char Battery75[] =
{
	0xF8,0x08,0xE8,0xE8,0xE8,0xE8,0x08,0xE8,0xE8,0xE8,0xE8,0x08,0xE8,0xE8,0xE8,0xE8,0x08,0x08,0x08,0x08,0x08,0x08,0xF8,0xE0,0x3F,0x20,0x2F,0x2F,0x2F,0x2F,0x20,0x2F,0x2F,0x2F,0x2F,0x20,
	0x2F,0x2F,0x2F,0x2F,0x20,0x20,0x20,0x20,0x20,0x20,0x3F,0x0F/*"G:\项目\1.可穿戴设备\UI\ui_icon\7.bmp",0*/
	/* (24 X 16 )*/
};
const unsigned char Battery50[] =
{
	0xF8,0x08,0xE8,0xE8,0xE8,0xE8,0x08,0xE8,0xE8,0xE8,0xE8,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0xF8,0xE0,0x3F,0x20,0x2F,0x2F,0x2F,0x2F,0x20,0x2F,0x2F,0x2F,0x2F,0x20,
	0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x3F,0x0F/*"G:\项目\1.可穿戴设备\UI\ui_icon\7.bmp",0*/
	/* (24 X 16 )*/
};

const unsigned char Battery25[] =
{
	0xF8,0x08,0xE8,0xE8,0xE8,0xE8,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0xF8,0xE0,0x3F,0x20,0x2F,0x2F,0x2F,0x2F,0x20,0x20,0x20,0x20,0x20,0x20,
	0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x3F,0x0F/*"G:\项目\1.可穿戴设备\UI\ui_icon\7.bmp",0*/
	/* (24 X 16 )*/
};


const unsigned char BatteryLOW[] =
{
	0xF8,0x08,0x08,0x08,0x08,0x68,0xE8,0xE8,0xC8,0xC8,0x88,0x88,0x88,0xC8,0xC8,0xE8,0xE8,0x68,0x08,0x08,0x08,0x08,0xF8,0xE0,0x3F,0x20,0x20,0x20,0x20,0x2C,0x2E,0x26,0x27,0x27,0x23,0x23,
	0x23,0x23,0x27,0x26,0x2E,0x2C,0x20,0x20,0x20,0x20,0x3F,0x0F/*"G:\项目\1.可穿戴设备\UI\ui_icon\低.bmp",0*/
	/* (24 X 16 )*/
};

const unsigned char BatteryCharge[] =
{
	0xF8,0x08,0x08,0x08,0x08,0x08,0x08,0x88,0x88,0xE8,0xE8,0xE8,0xE8,0xE8,0xC8,0xC8,0xC8,0x08,0x08,0x08,0x08,0x08,0xF8,0xE0,0x3F,0x20,0x20,0x20,0x20,0x20,0x20,0x23,0x23,0x2F,0x2F,0x2F,
	0x2F,0x2F,0x26,0x26,0x26,0x20,0x20,0x20,0x20,0x20,0x3F,0x0F/*"G:\项目\1.可穿戴设备\UI\ui_icon\8.bmp",0*/
	/* (24 X 16 )*/
};


#endif


