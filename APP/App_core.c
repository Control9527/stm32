#include "App_core.h"

#define NetTaskSize 1024    // 以太网
#define NetTaskRank 11
TaskHandle_t net_vTask;

#define Net1TaskSize 1024    // 以太网
#define Net1TaskRank 11
TaskHandle_t net1_vTask;

#define NetLEDTaskSize 512    // LED
#define NetLEDTaskRank 5
TaskHandle_t netled_vTask;

#define Net1LEDTaskSize 512    // LED
#define Net1LEDTaskRank 5
TaskHandle_t net1led_vTask;

void vNetLedTask(void *pvParameters)
{		
	uint32_t ulNotifiedValue     = 0;
	uint32_t ledToggleIntervalMs = 1000;
	
	for(;;)
	{
		
		/*
		* 参数 0x00      表示使用通知前不清除任务的通知值位，
		* 参数 ULONG_MAX 表示函数xTaskNotifyWait()退出前将任务通知值设置为0
		*/
		if( pdPASS == xTaskNotifyWait( 0x00, 0xffffffffUL, &ulNotifiedValue, ledToggleIntervalMs ) )
		{
			ledToggleIntervalMs  = ulNotifiedValue;		
		}
		
		//反转GPIO电平
		HAL_GPIO_TogglePin(LEDPort, LEDPin1);
	}
}


void vNet1LedTask(void *pvParameters)
{		
	uint32_t ulNotifiedValue     = 0;
	uint32_t ledToggleIntervalMs = 1000;
	
	for(;;)
	{
		
		/*
		* 参数 0x00      表示使用通知前不清除任务的通知值位，
		* 参数 ULONG_MAX 表示函数xTaskNotifyWait()退出前将任务通知值设置为0
		*/
		if( pdPASS == xTaskNotifyWait( 0x00, 0xffffffffUL, &ulNotifiedValue, ledToggleIntervalMs ) )
		{
			ledToggleIntervalMs  = ulNotifiedValue;		
		}
		
		//反转GPIO电平
		HAL_GPIO_TogglePin(LEDPort, LEDPin2);
	}
}


extern TaskHandle_t pvCreatedTask_vTask1;
void vStartTask(void *pvParameters)
{		
	NetInit();
	taskENTER_CRITICAL();  //进入临界区  即关掉所有中断
	xTaskCreate( vNetTask,"Net Task",(int)NetTaskSize,NULL,(unsigned long)NetTaskRank,&net_vTask );
	xTaskCreate( vNet1Task,"Net1 Task",(int)Net1TaskSize,NULL,(unsigned long)Net1TaskRank,&net1_vTask );
	xTaskCreate( vNetLedTask,"Net Led Task",(int)NetLEDTaskSize,NULL,(unsigned long)NetLEDTaskRank,&netled_vTask );
	xTaskCreate( vNet1LedTask,"Net1 Led Task",(int)Net1LEDTaskSize,NULL,(unsigned long)Net1LEDTaskRank,&net1led_vTask );
	taskEXIT_CRITICAL();  //退出临界区  即恢复中断

	vTaskDelete(pvCreatedTask_vTask1);
	
	while(1);
}

