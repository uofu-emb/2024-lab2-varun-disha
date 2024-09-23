/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>

#include "FreeRTOS.h"      // FreeRTOS header for task management
#include "task.h"

#include "pico/stdlib.h"   // Standard library for Pico SDK
#include "pico/multicore.h" // Library for handling multicore functionality
#include "pico/cyw43_arch.h" // Library for handling the CYW43 WiFi/BT chip

// Global variables
int count = 0;  // Counter to control the LED blink pattern
bool on = false; // Boolean flag to track LED state (on/off)

// Defines task priority
#define MAIN_TASK_PRIORITY      ( tskIDLE_PRIORITY + 1UL )
#define BLINK_TASK_PRIORITY     ( tskIDLE_PRIORITY + 2UL )

// Defines the task size to be minimal in stack memory
#define MAIN_TASK_STACK_SIZE    configMINIMAL_STACK_SIZE
#define BLINK_TASK_STACK_SIZE   configMINIMAL_STACK_SIZE

// Task function to handle LED blinking
void blink_task(__unused void *params) {
    // Initialize the CYW43 architecture 
    hard_assert(cyw43_arch_init() == PICO_OK);
    
    // Infinite loop to toggle the LED state
    while (true) {
        // Set the LED state according to the 'on' variable
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, on);
        
        // Toggle the LED state every 11 cycles
        if (count++ % 11) on = !on;
        
        // Delay for 500ms between each toggle
        vTaskDelay(500);
    }
}

// Task function to handle user input
void main_task(__unused void *params) {
    // Create the blink task
    xTaskCreate(blink_task, "BlinkThread",
                BLINK_TASK_STACK_SIZE, NULL, BLINK_TASK_PRIORITY, NULL);
    
    char c;  // Variable to store user input character
    
    // Infinite loop to process user input
    while(c = getchar()) {
        // Converting to lowercase letters to uppercase
        if (c <= 'z' && c >= 'a') putchar(c - 32);
        // Converting to uppercase letters to lowercase
        else if (c >= 'A' && c <= 'Z') putchar(c + 32);
        // Printing the character as is if it's not a letter
        else putchar(c);
    }
}

// Main function
int main(void) {
    // Initialize USB for standard I/O
    stdio_init_all();
    
    const char *rtos_name;
    rtos_name = "FreeRTOS"; // Assign RTOS name (not used further)
    
    // Creating an instance of the structure for the main task with specified stack size (tskTaskControlBlock assigned to typedef struct TaskHandle TaskHandle_t)
    TaskHandle_t task;
    
    // xTaskCreate, taking the function name, task size and task priority 
    xTaskCreate(main_task, "MainThread",
                MAIN_TASK_STACK_SIZE, NULL, MAIN_TASK_PRIORITY, &task);

    // Start the FreeRTOS scheduler, starting the task created and run
    vTaskStartScheduler();
    
    return 0; // Return 0 if the program exits 
}