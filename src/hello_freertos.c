/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>

#include "FreeRTOS.h"    
#include "task.h"

#include "pico/stdlib.h"  
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"
#include "main_functions.h"

int count = 0; 
bool on = false;

#define MAIN_TASK_PRIORITY      ( tskIDLE_PRIORITY + 1UL )
#define BLINK_TASK_PRIORITY     ( tskIDLE_PRIORITY + 2UL )

#define MAIN_TASK_STACK_SIZE    configMINIMAL_STACK_SIZE
#define BLINK_TASK_STACK_SIZE   configMINIMAL_STACK_SIZE

void blink_task(__unused void *params) {
    while (true) {
        led_blink(on, count);
    }
}

void main_task(__unused void *params) {
    xTaskCreate(blink_task, "BlinkThread",
                BLINK_TASK_STACK_SIZE, NULL, BLINK_TASK_PRIORITY, NULL);
    char c;
    while(c = getchar()) {
        char_inversion(c);
    }
}

int main(void) {
    stdio_init_all();
    const char *rtos_name;
    rtos_name = "FreeRTOS";
    TaskHandle_t task;
    
    // xTaskCreate, taking the function name, task size and task priority 
    xTaskCreate(main_task, "MainThread",
                MAIN_TASK_STACK_SIZE, NULL, MAIN_TASK_PRIORITY, &task);

    vTaskStartScheduler();
    
    return 0;
}