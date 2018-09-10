/*******************************************************************************
Copyright 2008 - 2016 ��������ӯ��������޹�˾. All rights reserved.
�ļ���:       gpio.h
����   : 
����   :       Jahol Fan
�汾   :       V1.0
�޸�   :   
������ڣ�
��ӯ�������http://www.edu118.com/
��ӯ����У��http://www.edu118.cn/
Notice    :������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;����Ȩ���У�����ؾ���
*******************************************************************************/
#ifndef GPIO_H
#define GPIO_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */
#include "stm32f4xx.h"
/*********************************************************************
 * TYPEDEFS
 */
/*********************************************************************
*  EXTERNAL VARIABLES
*/

/*********************************************************************
 * CONSTANTS
 */
//GPIO����ר�ú궨��
#define GPIO_MODE_IN    	0		//��ͨ����ģʽ
#define GPIO_MODE_OUT		1		//��ͨ���ģʽ
#define GPIO_MODE_AF		2		//AF����ģʽ
#define GPIO_MODE_AIN		3		//ģ������ģʽ

#define GPIO_SPEED_2M		0		//GPIO�ٶ�2Mhz
#define GPIO_SPEED_25M		1		//GPIO�ٶ�25Mhz
#define GPIO_SPEED_50M		2		//GPIO�ٶ�50Mhz
#define GPIO_SPEED_100M		3		//GPIO�ٶ�100Mhz

#define GPIO_PUPD_NONE		0		//����������
#define GPIO_PUPD_PU		1		//����
#define GPIO_PUPD_PD		2		//����
#define GPIO_PUPD_RES		3		//���� 

#define GPIO_OTYPE_PP		0		//�������
#define GPIO_OTYPE_OD		1		//��©��� 
//GPIO���ű�Ŷ���
#define PIN0				1<<0
#define PIN1				1<<1
#define PIN2				1<<2
#define PIN3				1<<3
#define PIN4				1<<4
#define PIN5				1<<5
#define PIN6				1<<6
#define PIN7				1<<7
#define PIN8				1<<8
#define PIN9				1<<9
#define PIN10				1<<10
#define PIN11				1<<11
#define PIN12				1<<12
#define PIN13				1<<13
#define PIN14				1<<14
#define PIN15				1<<15 
/*********************************************************************
 * MACROS
 */

/*********************************************************************
 *PUBLIC FUNCTIONS DECLARE
 */
void GPIO_set(GPIO_TypeDef* GPIOx,u32 BITx,u32 MODE,u32 OTYPE,u32 OSPEED,u32 PUPD);
void GPIO_AFset(GPIO_TypeDef* GPIOx,u8 BITx,u8 AFx);



/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* GPIO_H */
