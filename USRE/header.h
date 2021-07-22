#ifndef HEADER_H_
#define HEADER_H_


#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "list.h"
#include "event_groups.h"
#include "portable.h"

#include "stm32h7xx.h"
#include "core_cm7.h"
#include "stm32h7xx_hal.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#include "RingBuff.h"

#include "Bsp_mpu.h"
#include "Bsp_timer.h"
#include "Bsp_gpio.h"
#include "Bsp_init.h"

#include "tcp_client.h"
#include "tcp_server.h"

#include "App_net.h"
#include "App_core.h"




#endif


