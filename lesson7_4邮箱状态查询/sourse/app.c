#include "tinyOS.h"



tTask tTask1;
tTask tTask2;
tTask	tTask3;
tTask tTask4;

tTastStack task1Env[1024];
tTastStack task2Env[1024];
tTastStack task3Env[1024];
tTastStack task4Env[1024];

//定义两个等待队列
t_event event_wait_timeout;
t_event event_wait_normal;


t_mbox mbox2;
t_mbox_info mbox_info;
void * msgbuffer2[20];

uint32_t msg[20];

int task1flag;



void task1Entry (void *param)
{
	tSetSysTickPeriod(10);

	for(;;)
	{

		task1flag = 0;
		tTaskDelay(1);
		task1flag = 1;
		tTaskDelay(1);
	}

}

// 

int task2flag;
void task2Entry (void *param)
{
	int i;
	t_mbox_init(&mbox2, 20, msgbuffer2);
	
	for(;;)
	{
		for(i = 0; i < 20; i ++)
		{
			msg[i] = i;
			t_mbox_notify(&mbox2, &msg[i] , tMBOXSendFront);
			t_mbox_get_info(&mbox2, &mbox_info);
			
		}

		tTaskDelay(100);
		
		task2flag = 0;
		tTaskDelay(1);
		task2flag = 1;
		tTaskDelay(1);

	}
}

int task3flag;
void task3Entry (void *param)
{

	for(;;)
	{

		task3flag = 0;
		tTaskDelay(1);
		task3flag = 1;
		tTaskDelay(1);

	}
}

int task4flag;
void task4Entry (void *param)
{
	for(;;)
	{	
		task4flag = 0;
		tTaskDelay(1);
		task4flag = 1;
		tTaskDelay(1);
		
	}

}

void app_init()
{
	// 初始化任务1和任务2结构，传递运行的起始地址，想要给任意参数，以及运行堆栈空间
	tTaskInit(&tTask1, task1Entry, (void* )0x11111111, 0, &task1Env[1024]);
	tTaskInit(&tTask2, task2Entry, (void *)0x22222222, 0, &task2Env[1024]);
	
	tTaskInit(&tTask3, task3Entry, (void *)0x33333333, 1, &task3Env[1024]);
	tTaskInit(&tTask4, task4Entry, (void *)0x44444444, 1, &task4Env[1024]);

}




