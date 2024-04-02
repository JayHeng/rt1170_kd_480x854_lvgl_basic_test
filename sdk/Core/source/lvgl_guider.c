/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "FreeRTOS.h"
#include "task.h"

#include "fsl_debug_console.h"
#include "lvgl_support.h"
#include "pin_mux.h"
#include "board.h"
#include "lvgl.h"
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"
#include "lvgl_demo_utils.h"
#include "lvgl_freertos.h"

#include "fsl_soc_src.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
static volatile bool s_lvgl_initialized = false;
lv_ui guider_ui;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

#if LV_USE_LOG
static void print_cb(const char *buf)
{
    PRINTF("\r%s\n", buf);
}
#endif

static uint32_t get_idle_time_cb(void)
{
    return (getIdleTaskTime() / 1000);
}

static void reset_idle_time_cb(void)
{
    resetIdleTaskTime();
}

static void AppTask(void *param)
{
#if LV_USE_LOG
    lv_log_register_print_cb(print_cb);
#endif

    lv_timer_register_get_idle_cb(get_idle_time_cb);
    lv_timer_register_reset_idle_cb(reset_idle_time_cb);
    lv_port_pre_init();
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();

    s_lvgl_initialized = true;

    setup_ui(&guider_ui);
    events_init(&guider_ui);
    custom_init(&guider_ui);

    for (;;)
    {
        lv_task_handler();
        vTaskDelay(5);
    }
}

/*******************************************************************************
 * Code
 ******************************************************************************/
#define RPI_ADDR  0x45
/* Get frequency of lpi2c clock */
#define LPI2C_CLOCK_FREQUENCY (CLOCK_GetFreq(kCLOCK_OscRc48MDiv2))
#define RPI_I2C_BASEADDR  LPI2C5

void talk_to_raspi(void)
{
    uint8_t tmp;
    uint8_t brightness = 0x80;

    BOARD_LPI2C_Init(RPI_I2C_BASEADDR, LPI2C_CLOCK_FREQUENCY);

    VIDEO_DelayMs(2000);

    //init_cmd_check
    //read_reg(RPI_ADDR, 0x80, &tmp);
    BOARD_LPI2C_Receive(RPI_I2C_BASEADDR, RPI_ADDR, 0x80, 1, &tmp, 1);
    PRINTF("reg 0x80 is 0x%x\r\n", tmp);

    //rpi_display_screen_power_up
    //write_reg(RPI_ADDR, 0x85, 0x00);
    tmp = 0;
    BOARD_LPI2C_Send(RPI_I2C_BASEADDR, RPI_ADDR, 0x85, 1, &tmp, 1);
    VIDEO_DelayMs(800);
    //write_reg(RPI_ADDR, 0x85, 0x01);
    tmp = 0x01;
    BOARD_LPI2C_Send(RPI_I2C_BASEADDR, RPI_ADDR, 0x85, 1, &tmp, 1);
    VIDEO_DelayMs(800);
    //write_reg(RPI_ADDR, 0x81, 0x04);
    tmp = 0x04;
    BOARD_LPI2C_Send(RPI_I2C_BASEADDR, RPI_ADDR, 0x81, 1, &tmp, 1);

    PRINTF("done\r\n");
    VIDEO_DelayMs(800);
    //rpi_display_set_bright
    //write_reg(RPI_ADDR, 0x86, brightness);
    BOARD_LPI2C_Send(RPI_I2C_BASEADDR, RPI_ADDR, 0x86, 1, &brightness, 1);
}

/*!
 * @brief Main function
 */
int main(void)
{
    BaseType_t stat;

    /* Init board hardware. */
    BOARD_ConfigMPU();
    BOARD_BootClockRUN();

    /*
     * Reset the displaymix, otherwise during debugging, the
     * debugger may not reset the display, then the behavior
     * is not right.
     */
    SRC_AssertSliceSoftwareReset(SRC, kSRC_DisplaySlice);

    BOARD_InitLpuartPins();
    BOARD_InitMipiPanelPins();
    BOARD_MIPIPanelTouch_I2C_Init();
    BOARD_InitDebugConsole();
    DEMO_InitUsTimer();

    stat = xTaskCreate(AppTask, "lvgl", configMINIMAL_STACK_SIZE + 8000, NULL, tskIDLE_PRIORITY + 2, NULL);

    if (pdPASS != stat)
    {
        PRINTF("Failed to create lvgl task");
        while (1)
            ;
    }

    vTaskStartScheduler();

    for (;;)
    {
    } /* should never get here */
}

/*!
 * @brief Malloc failed hook.
 */
void vApplicationMallocFailedHook(void)
{
    PRINTF("Malloc failed. Increase the heap size.");

    for (;;)
        ;
}

/*!
 * @brief FreeRTOS tick hook.
 */
void vApplicationTickHook(void)
{
    if (s_lvgl_initialized)
    {
        lv_tick_inc(1);
    }
}

/*!
 * @brief Stack overflow hook.
 */
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    (void)pcTaskName;
    (void)xTask;

    for (;;)
        ;
}
