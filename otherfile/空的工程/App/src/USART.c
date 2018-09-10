#include "USART.h"



uint8 RX_data[512];
uint8 flag=0;
uint8 i=0;
uint8 Timeout_flag;



/********************************************************************************************
*  �� �� ���� usart_Io_Init
*  ��    ��:  USART1 ��ʼ��
*  ��������� ��   
*  ��������� ��
*  �� �� ֵ:  ��
*  ��    ��:  �غ�
*  �������:  2018-07-18
*  ע������:  ��
********************************************************************************************/


void usart_Io_Init (void)
{
    RCC->AHB1ENR |=0x01<<0;//����PA�˿�
    GPIOA->MODER &=~((0x03<<18)|(0x03<<20));//����
    GPIOA->MODER |=(0x02<<18)|(0x02<<20);//����Ϊ����ģʽ
    GPIOA->OTYPER &= ~(0X01<<9);//PA9�������
    GPIOA->OSPEEDR &=~(0X03<<18);
    GPIOA->OSPEEDR |=0X01<<18;
    GPIOA->PUPDR &=~(0X03<<20);//��������
    GPIOA->PUPDR |=0X01<<20;
    GPIOA->AFR[1] &=~((0x0f<<4)|(0x0f<<8));//����
    GPIOA->AFR[1] |=(0x07<<4)|(0x07<<8);//����ΪAF7
    
} 



void USART1_SET (uint32 Baud )
{
    float USART_DIV;
    uint16 Div_Man;
    float Div_f;
    RCC->APB2ENR  |=0x01<<4;//USART1ʱ��ʹ�ܣ�
    RCC->APB2RSTR |=0X01<<4;
    RCC->APB2RSTR &=~(0X01<<4);//��λ������
    USART1->CR1 |=(0X01<<2)|(0X01<<3);//�������������ʹ��
    USART1->CR2 &=~(0X03<<12);//λֹͣ
    
    
    USART_DIV=(float)84000000/(8*2*Baud);
    Div_Man =USART_DIV ;
    Div_f=USART_DIV-Div_Man;
    USART1->BRR =(Div_Man <<4)|((uint16 )(Div_f *16));
    
    USART1->CR1 |= 0X01<<5;  //���ڽ����ж�ʹ��
    USART1->SR &= ~(0X01<<5); //��־λ����
    NVIC_SetPriorityGrouping(7-2); //����  
    NVIC_EncodePriority(7-2,0,0);
    NVIC_SetPriority(USART1_IRQn,NVIC_EncodePriority(7-2,0,0));//�������ȼ�
    NVIC_EnableIRQ(USART1_IRQn); //�ж�ʹ��
    
    
    USART1->CR1 |=(0X01<<13);// USART1ʹ��
    
    
    

    
}




void USART1_IRQHandler(void)
 {
     uint8 Receive_data;
 
    if(USART1->SR &(0X01<<5))
    {
        Timeout_flag=3;
        Receive_data=USART1->DR ;
        if(flag==0)
        {
             RX_data[i++]=Receive_data; 
        }
        else 
        {
            flag=1;
        }
    }
 }
void send_data(uint8 data)
{
    while(!(USART1->SR &(0x01<<7)));
    
     USART1->DR =data;
    
}

void send_String (uint8 *String )
{
    while(*String !='\0')
    {
       send_data(*String ) ;
       String ++;
    }
}



//void R_data(void)
//{

//    uint8 Receive_data;
// 
//    if(USART1->SR &(0X01<<5))
//    {
//        Receive_data=USART1->DR ;
//        if((Receive_data!='$')&&(flag==0))
//        {
//             RX_data[i++]=Receive_data; 
//        }
//        else 
//        {
//            flag=1;
//        }
//    }
//}

void P_R_data(void)
{
    if(flag )
    {
        send_String (RX_data);
        if(strcmp((const char *)RX_data,"Led_ON")==0)
        {
             Led_state_control(0x0f);
        }
        else if(strcmp((const char *)RX_data,"Led_OFF")==0)
        {
             Led_state_control(0x00);    
        }
        else if(strcmp((const char *)RX_data,"Beep_ON")==0)
        {
             //Beep_State_Contrl(1);
        }
        else if(strcmp((const char *)RX_data,"Beep_OFF")==0)
        {
            // Beep_State_Contrl(0);
        }
        memset(RX_data,0,i);
        flag=0;
        i=0;
    }
    
}










#pragma import(__use_no_semihosting_swi) //???????

struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;

int fputc(int ch, FILE *f) 
{
	while((USART1->SR & (0X01<<7)) == 0);
		USART1->DR=ch;
    return (ch);
}
int ferror(FILE *f) {
  /* Your implementation of ferror */
  return EOF;
}


void _ttywrch(int ch) {
  while((USART1->SR &(0X01<<7))==0);
		USART1->DR=ch;
}


void _sys_exit(int return_code) {
label:  goto label;  /* endless loop */
}

