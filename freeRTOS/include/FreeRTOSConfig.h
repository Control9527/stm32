/*
    FreeRTOS V9.0.0 - Copyright (C) 2016 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>>> AND MODIFIED BY <<<< the FreeRTOS exception.

    ***************************************************************************
    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<
    ***************************************************************************

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available on the following
    link: http://www.freertos.org/a00114.html

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that is more than just the market leader, it     *
     *    is the industry's de facto standard.                               *
     *                                                                       *
     *    Help yourself get started quickly while simultaneously helping     *
     *    to support the FreeRTOS project by purchasing a FreeRTOS           *
     *    tutorial book, reference manual, or both:                          *
     *    http://www.FreeRTOS.org/Documentation                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
    the FAQ page "My application does not run, what could be wrong?".  Have you
    defined configASSERT()?

    http://www.FreeRTOS.org/support - In return for receiving this top quality
    embedded software for free we request you assist our global community by
    participating in the support forum.

    http://www.FreeRTOS.org/training - Investing in training allows your team to
    be as productive as possible as early as possible.  Now you can receive
    FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
    Ltd, and the world's leading authority on the world's leading RTOS.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
    Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

    http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
    Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and commercial middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H


/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html.
 *----------------------------------------------------------*/

#include <stdint.h>
extern uint32_t SystemCoreClock;

/* The following definition allows the startup files that ship with the IDE
to be used without modification when the chip used includes the PMU CM001
errata. */
#define WORKAROUND_PMU_CM001					0

#define configUSE_TIME_SLICING					1

#define configUSE_PORT_OPTIMISED_TASK_SELECTION	1
#define configUSE_PREEMPTION					1   /* 使能抢占式调度，否则用合作式调度，默认我们都是用抢占式 */
#define configUSE_IDLE_HOOK						0 /* 空闲任务钩子函数，如果配置为1，这个钩子函数需要用户自己编写 */
#define configUSE_TICK_HOOK						0   /* 时基任务钩子函数，如果配置为1，这个钩子函数需要用户自己编写*/
#define configCPU_CLOCK_HZ						( SystemCoreClock )    /* 系统时钟，单位为HZ */
#define configTICK_RATE_HZ						( ( TickType_t ) 1000 ) /* SysTick中断周期，单位为HZ，2000HZ即0.5ms中断一次 */
#define configMAX_PRIORITIES					( 14 ) /* 任务能使用最大优先级个数，数字越大优先级越高，范围为：0~configMAX_PRIORITIES-1
                                               最低的0由系统分配给空闲任务，每个任务的优先级可以相同 */
#define configMINIMAL_STACK_SIZE				( ( unsigned short ) 256 )
#define configTOTAL_HEAP_SIZE					( ( size_t ) ( 1024 * 55 ) )  /* 堆空间大小，内核在创建各种对象时需要用到，单位为字节 */
#define configMAX_TASK_NAME_LEN					( 15 )   /* 任务名称的长度，即字符串的长度 */
#define configUSE_TRACE_FACILITY				1
#define configUSE_16_BIT_TICKS					0   /* SysTick Counter的宽度，0表示32bit，1表示16bit，STM32用的是32bit */
#define configIDLE_SHOULD_YIELD					1  /* 上下文切换强制使能，即当前任务执行完毕之后还有剩余的时间片，可以强制自己放弃
                                              剩余的时间片，然后执行上下文切换去执行其他的任务*/
#define configUSE_MUTEXES						    1
#define configQUEUE_REGISTRY_SIZE				8
#define configCHECK_FOR_STACK_OVERFLOW		0              //2改为0
#define configUSE_RECURSIVE_MUTEXES				1
#define configUSE_MALLOC_FAILED_HOOK			0              //1改为0
#define configUSE_APPLICATION_TASK_TAG		0
#define configUSE_COUNTING_SEMAPHORES			1
#define configGENERATE_RUN_TIME_STATS			0

#define INCLUDE_uxTaskGetStackHighWaterMark 1  //使能这个函数  查看堆栈剩余多少

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 		0
#define configMAX_CO_ROUTINE_PRIORITIES ( 2 )

/* Software timer definitions. */  /* 软件定时器配置 */
#define configUSE_TIMERS				1
#define configTIMER_TASK_PRIORITY		( 13 )   //定时器优先级
#define configTIMER_QUEUE_LENGTH		10
#define configTIMER_TASK_STACK_DEPTH	( configMINIMAL_STACK_SIZE * 4 )

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */
#define INCLUDE_vTaskPrioritySet		1
#define INCLUDE_uxTaskPriorityGet		1
#define INCLUDE_vTaskDelete				1
#define INCLUDE_vTaskCleanUpResources	1
#define INCLUDE_vTaskSuspend			1
#define INCLUDE_vTaskDelayUntil			1
#define INCLUDE_vTaskDelay				1   /* vTaskDelay 为阻塞延时函数，常用，单位为ms */
/*
vTaskDelay延时的时间是切换后其他任务执行的时间，不包括切换任务等需要的时间
vTaskDelayUntil延时时间是第一次执行此函数后到下一次执行此函数的时间
*/





/* Cortex-M specific definitions. */
#ifdef __NVIC_PRIO_BITS
	/* __BVIC_PRIO_BITS will be specified when CMSIS is being used. */
	#define configPRIO_BITS       		__NVIC_PRIO_BITS
#else
	#define configPRIO_BITS       		6        /* 15 priority levels */
#endif

/* The lowest interrupt priority that can be used in a call to a "set priority"
function. */
//中断最低优先级
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			0x3f

/* The highest interrupt priority that can be used by any interrupt service
routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
PRIORITY THAN THIS! (higher priorities are lower numeric values. */
//系统管理的最高优先级
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	5   //管理中断

/* Interrupt priorities used by the kernel port layer itself.  These are generic
to all Cortex-M ports, and do not rely on any particular library functions. */
#define configKERNEL_INTERRUPT_PRIORITY 		( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
	
/* Normal assert() semantics without relying on the provision of an assert.h
header file. */
#define configASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }	
	
/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
standard names.  WORKAROUND_PMU_CM001 is defined at the top of this file. */
#if WORKAROUND_PMU_CM001 == 1
	#define xPortPendSVHandler PendSV_Handler_Veneer
#else
	#define xPortPendSVHandler PendSV_Handler
#endif
#define vPortSVCHandler SVC_Handler
#define xPortSysTickHandler SysTick_Handler


///* Demo application specific settings. */
//#if defined( PART_XMC4500 )
//	/* Hardware includes. */
//	#include "XMC4500.h"
//	#include "System_XMC4500.h"

//	/* Configure pin P3.9 for the LED. */
//	#define configCONFIGURE_LED() ( PORT3->IOCR8 = 0x00008000 )
//	/* To toggle the single LED */
//	#define configTOGGLE_LED()	( PORT3->OMR =	0x02000200 )
//#elif defined( PART_XMC4400 )
//	/* Hardware includes. */
//	#include "XMC4400.h"
//	#include "System_XMC4200.h"

//	/* Configure pin P5.2 for the LED. */
//	#define configCONFIGURE_LED() ( PORT5->IOCR0 = 0x00800000 )
//	/* To toggle the single LED */
//	#define configTOGGLE_LED()	( PORT5->OMR =	0x00040004 )
//#elif defined( PART_XMC4200 )
//	/* Hardware includes. */
//	#include "XMC4200.h"
//	#include "System_XMC4200.h"

//	/* Configure pin P2.1 for the LED. */
//	#define configCONFIGURE_LED() PORT2->IOCR0 = 0x00008000; PORT2->HWSEL &= ~0x0000000cUL
//	/* To toggle the single LED */
//	#define configTOGGLE_LED()	( PORT2->OMR =	0x00020002 )
//#else
//	#error Part number not specified in project options
//#endif


#endif /* FREERTOS_CONFIG_H */

