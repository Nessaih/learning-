#ifndef __SPI_H_
#define __SPI_H_

#include "stm32f4xx.h"
#include "type.h"
#include "sys.h"
#include "delay.h"

#define SPI_SCK_OH		PBout(3) = 1
#define SPI_SCK_OL		PBout(3) = 0
#define SPI_MOSI_OH		PBout(5) = 1
#define SPI_MOSI_OL		PBout(5) = 0

extern void Spi_Io_Init(void);
extern void Spi_Write_Byte(uint8 data);


#endif


