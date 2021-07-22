#include "header.h"

#define StartTaskSize 512
#define StartTaskRank 12
TaskHandle_t pvCreatedTask_vTask1;

int main(void)
{	
	InitMCU();
	
	xTaskCreate( vStartTask,
				 "Start Task",
				 (int)StartTaskSize,
				  NULL,
				 (unsigned long)StartTaskRank,
				  &pvCreatedTask_vTask1 );

	vTaskStartScheduler();  //������������� 
}


