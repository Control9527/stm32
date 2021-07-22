#include "Bsp_timer.h"

#define TIM_TIME_INSTANCE		TIM2
#define TIM_TIME_IRQx			TIM2_IRQn
#define TIM_TIME_CLK_ENABLE()	__HAL_RCC_TIM2_CLK_ENABLE()

#define LWIPTIM					TIM7


//定时器句柄
TIM_HandleTypeDef 				TIMx_TIME_Handler;   


//Prescaler：时钟预分频数
//Period：自动重装值
//200M/200/100有0.1ms
void TIMx_Timer_Init(void)
{  
    TIMx_TIME_Handler.Instance = TIM_TIME_INSTANCE;                          
    TIMx_TIME_Handler.Init.Prescaler = 100-1;                     
    TIMx_TIME_Handler.Init.CounterMode = TIM_COUNTERMODE_UP;    
    TIMx_TIME_Handler.Init.Period = 200-1;                        
    TIMx_TIME_Handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_Base_Init(&TIMx_TIME_Handler);
    
	//此函数中已经启动更新中断
    HAL_TIM_Base_Start_IT(&TIMx_TIME_Handler);    
}


//此函数会被HAL_TIM_Base_Init()函数调用
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM_TIME_INSTANCE)
	{
		TIM_TIME_CLK_ENABLE();            
		HAL_NVIC_SetPriority(TIM_TIME_IRQx,1,0);    
		HAL_NVIC_EnableIRQ(TIM_TIME_IRQx);          
	}  	
}

void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIMx_TIME_Handler);
}


//自定义的延时函数
volatile uint32_t TimDelayNumber;
void delay_100us(uint32_t us)
{
	TimDelayNumber = us;
	while(TimDelayNumber != 0);
}
void delay_ms(uint32_t ms)
{
	TimDelayNumber = ms * 10;
	while(TimDelayNumber != 0);
}
void delay_s(uint32_t s)
{
	TimDelayNumber = s * 10000;
	while(TimDelayNumber != 0);
}

//定时器的计算器
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM_TIME_INSTANCE)
    {
		//0.1ms		
		//延时函数
		if(TimDelayNumber != 0)
		{
			TimDelayNumber--;
		}
    }
	else if(htim->Instance == LWIPTIM)
	{
		HAL_IncTick();
	}	
}









