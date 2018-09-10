#include "key.h"
#include "test.h"

void key_init(void)
{
	//KEY1 --PA0
	RCC->AHB1ENR |= 0x01; 		//��ʱ�ӣ�GPIOA�ɶ�д
	GPIOA->MODER &= ~(3 << 0);  //���ùܽ�ģʽ
	GPIOA->PUPDR &= ~(3 << 0);	//��������
	GPIOA->PUPDR |= (2 << 0);		
	
	//KEY2 --PE2
	RCC->AHB1ENR |= 0x10;//��ʱ�ӣ�GPIOE�ɶ�д
	
	��д������
}


int key_scan(void)
{
	static int key = 1;
	if(KEY1 && key)
	{
		key = 0;
		delay(1000000);
		if(KEY1)
		{
			return 1;
		}
	}
	else if(!KEY1 && key == 0)
		key = 1;
	return 0;
}
