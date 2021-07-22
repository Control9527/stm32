#include "Bsp_gpio.h"

GpioTable_ GpioTable[GPIONUMBER] = 
						{
							[LED_R] = 
								{
									.GpioPin = LEDPin1,
									.GpioSpeed = GPIO_SPEED_FREQ_LOW,
									.GpioMode = GPIO_MODE_OUTPUT_PP,
									.GpioPull = GPIO_PULLDOWN,
									.GpioPort = LEDPort,
									.functon = RCC_GPIOD_ENABLE,
								},
							[LED_G] = 
								{
									.GpioPin = LEDPin2,
									.GpioSpeed = GPIO_SPEED_FREQ_LOW,
									.GpioMode = GPIO_MODE_OUTPUT_PP,
									.GpioPull = GPIO_PULLDOWN,
									.GpioPort = LEDPort,
									.functon = RCC_GPIOD_ENABLE,
								},
							[LED_B] = 
								{
									.GpioPin = LEDPin3,
									.GpioSpeed = GPIO_SPEED_FREQ_LOW,
									.GpioMode = GPIO_MODE_OUTPUT_PP,
									.GpioPull = GPIO_PULLDOWN,
									.GpioPort = LEDPort,
									.functon = RCC_GPIOD_ENABLE,
								}
						};

void RCC_GPIOC_ENABLE(void)
{
	__HAL_RCC_GPIOC_CLK_ENABLE();
}
void RCC_GPIOD_ENABLE(void)
{
	__HAL_RCC_GPIOD_CLK_ENABLE();
}
void RCC_GPIOE_ENABLE(void)
{
	__HAL_RCC_GPIOE_CLK_ENABLE();
}

						
void GpioMoreInit(uint8_t num)
{
	GPIO_InitTypeDef GPIO_Initure;

	GpioTable[num].functon();
	
    GPIO_Initure.Pin = GpioTable[num].GpioPin;		
    GPIO_Initure.Mode = GpioTable[num].GpioMode;  		
    GPIO_Initure.Pull = GpioTable[num].GpioPull;         			
    GPIO_Initure.Speed = GpioTable[num].GpioSpeed;  	
    HAL_GPIO_Init(GpioTable[num].GpioPort,&GPIO_Initure);     		
}	

void Gpio_Init(void)
{
	for(char i = 0; i < GPIONUMBER; i++)
	{
		GpioMoreInit(i);
	}
}



