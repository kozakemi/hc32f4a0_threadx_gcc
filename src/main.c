/**
 *******************************************************************************
 * @file  gpio/gpio_output/source/main.c
 * @brief Main program of GPIO for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll.h"
#include "ev_hc32f4a0_lqfp176_bsp.h"
#include "ev_hc32f4a0_lqfp176.h"
#include "tx_api.h"
#include "SEGGER_RTT.h"

/**
 * @addtogroup HC32F4A0_DDL_Examples
 * @{
 */

/**
 * @addtogroup GPIO_OUTPUT
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* LED_G Port/Pin definition */
#define LED_G_PORT          (GPIO_PORT_C)
#define LED_G_PIN           (GPIO_PIN_09)
/* LED toggle definition */
#define LED_G_TOGGLE()      (GPIO_TogglePins(LED_G_PORT, LED_G_PIN))

#define DLY_MS              (2000UL)

/* ThreadX definitions */
#define THREAD_STACK_SIZE   1024
#define THREAD_PRIORITY     3

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
/* ThreadX objects */
TX_THREAD thread_led;
UCHAR thread_led_stack[THREAD_STACK_SIZE];

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  LED Thread Entry Function
 * @param  thread_input: Thread input parameter
 * @retval None
 */
static void thread_led_entry(ULONG thread_input)
{
    (void)thread_input;
    
    for (;;) {
        LED_G_TOGGLE();
        SEGGER_RTT_printf(0, "LED toggled\n");
        tx_thread_sleep(TX_TIMER_TICKS_PER_SECOND * 2); /* Sleep for 2 seconds */
    }
}
/**
 * @brief  LED Init
 * @param  None
 * @retval None
 */
static void LED_Init(void)
{
    stc_gpio_init_t stcGpioInit;

    (void)GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinState = PIN_STAT_RST;
    stcGpioInit.u16PinDir = PIN_DIR_OUT;
    (void)GPIO_Init(LED_G_PORT, LED_G_PIN, &stcGpioInit);
     GPIO_SetDebugPort(GPIO_PIN_TDO, DISABLE);
     GPIO_SetDebugPort(GPIO_PIN_TRST, DISABLE);
}

/**
 * @brief  Main function of GPIO project
 * @param  None
 * @retval int32_t return value, if needed
 */
int main(void)
{
    /* Register write enable for some required peripherals. */
    LL_PERIPH_WE(LL_PERIPH_ALL);
    /* Initialize BSP system clock. */
    BSP_CLK_Init();
    /* Initialize SEGGER RTT */
    SEGGER_RTT_Init();
    SEGGER_RTT_printf(0, "SEGGER RTT initialized successfully!\n");
    /* LED initialize */
    LED_Init();
    /* Register write protected for some required peripherals. */
    LL_PERIPH_WP(LL_PERIPH_ALL);
    
    /* Initialize ThreadX kernel */
    tx_kernel_enter();
    
    /* Should never reach here */
    for (;;) {
        /* Empty loop */
    }
}

/**
 * @brief  ThreadX application define function
 * @param  first_unused_memory: First unused memory address
 * @retval None
 */
void tx_application_define(void *first_unused_memory)
{
    (void)first_unused_memory;
    
    /* Create LED thread */
    tx_thread_create(&thread_led,
                     "LED Thread",
                     thread_led_entry,
                     0,
                     thread_led_stack,
                     THREAD_STACK_SIZE,
                     THREAD_PRIORITY,
                     THREAD_PRIORITY,
                     TX_NO_TIME_SLICE,
                     TX_AUTO_START);
}

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
