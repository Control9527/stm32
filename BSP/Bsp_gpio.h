#ifndef BSP_GPIO_H_
#define BSP_GPIO_H_

#include "header.h"

//LEDµÆ
#define LEDPin1			GPIO_PIN_10
#define LEDPin2			GPIO_PIN_11
#define LEDPin3			GPIO_PIN_12
#define LEDPort			GPIOD


typedef struct  __attribute__ ((__packed__))
{
	uint32_t GpioPin;
	uint32_t GpioSpeed;	
	uint32_t GpioMode;
	uint32_t GpioPull;
	
	GPIO_TypeDef* GpioPort;
	void (*functon)(void);
}GpioTable_;

typedef enum 
{
	LED_R = 0,
	LED_G,
	LED_B,
	GPIONUMBER
}GpioName_;


void RCC_GPIOC_ENABLE(void);
void RCC_GPIOD_ENABLE(void);
void RCC_GPIOE_ENABLE(void);

void Gpio_Init(void);


#endif
