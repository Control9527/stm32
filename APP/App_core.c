#include "App_core.h"

#define NetTaskSize 1024    // ��̫��
#define NetTaskRank 11
TaskHandle_t net_vTask;

#define Net1TaskSize 1024    // ��̫��
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
		* ���� 0x00      ��ʾʹ��֪ͨǰ����������ֵ֪ͨλ��
		* ���� ULONG_MAX ��ʾ����xTaskNotifyWait()�˳�ǰ������ֵ֪ͨ����Ϊ0
		*/
		if( pdPASS == xTaskNotifyWait( 0x00, 0xffffffffUL, &ulNotifiedValue, ledToggleIntervalMs ) )
		{
			ledToggleIntervalMs  = ulNotifiedValue;		
		}
		
		//��תGPIO��ƽ
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
		* ���� 0x00      ��ʾʹ��֪ͨǰ����������ֵ֪ͨλ��
		* ���� ULONG_MAX ��ʾ����xTaskNotifyWait()�˳�ǰ������ֵ֪ͨ����Ϊ0
		*/
		if( pdPASS == xTaskNotifyWait( 0x00, 0xffffffffUL, &ulNotifiedValue, ledToggleIntervalMs ) )
		{
			ledToggleIntervalMs  = ulNotifiedValue;		
		}
		
		//��תGPIO��ƽ
		HAL_GPIO_TogglePin(LEDPort, LEDPin2);
	}
}


extern TaskHandle_t pvCreatedTask_vTask1;
void vStartTask(void *pvParameters)
{		
	NetInit();
	taskENTER_CRITICAL();  //�����ٽ���  ���ص������ж�
	xTaskCreate( vNetTask,"Net Task",(int)NetTaskSize,NULL,(unsigned long)NetTaskRank,&net_vTask );
	xTaskCreate( vNet1Task,"Net1 Task",(int)Net1TaskSize,NULL,(unsigned long)Net1TaskRank,&net1_vTask );
	xTaskCreate( vNetLedTask,"Net Led Task",(int)NetLEDTaskSize,NULL,(unsigned long)NetLEDTaskRank,&netled_vTask );
	xTaskCreate( vNet1LedTask,"Net1 Led Task",(int)Net1LEDTaskSize,NULL,(unsigned long)Net1LEDTaskRank,&net1led_vTask );
	taskEXIT_CRITICAL();  //�˳��ٽ���  ���ָ��ж�

	vTaskDelete(pvCreatedTask_vTask1);
	
	while(1);
}

