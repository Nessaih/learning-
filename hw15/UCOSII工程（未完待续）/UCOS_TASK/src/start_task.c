#include "start_task.h"


OS_STK  START_TASK_STACK[START_TASK_STACK_SIZE];


void Start_Task(void *pdata)
{
    pdata = pdata;    //��ֹ�������Ż�
    while(1)
    {
         OSTimeDly(100);
    }
}