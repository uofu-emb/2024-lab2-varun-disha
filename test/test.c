#include <stdio.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <unity.h>
#include "unity_config.h"
#include "pico/cyw43_arch.h"
#include "main_functions.h"

void setUp(void) {}

void tearDown(void) {}

void test_variable_assignment()
{
    int x = 1;
    TEST_ASSERT_TRUE_MESSAGE(x == 1,"Variable assignment failed.");
}

void test_multiplication(void)
{
    int x = 30;
    int y = 6;
    int z = x / y;
    TEST_ASSERT_TRUE_MESSAGE(z == 5, "Multiplication of two integers returned incorrect value.");
}

void test_led_pin(){
    int count = 0;
    bool on = false;
    bool prev_state = false;   
    int gpio_state = false;
    int check_count = 0;
    hard_assert(cyw43_arch_init() == PICO_OK);
    for(int loop_count = 0; loop_count <111; loop_count ++)
    {
        LedBlinkResult result = led_blink(on, count);
        gpio_state = cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN);
        TEST_ASSERT_EQUAL_MESSAGE(gpio_state, result.on, "TEST FAILED");
        if ((result.count - 1) % 11){
            TEST_ASSERT_NOT_EQUAL_MESSAGE(gpio_state, prev_state, "TEST FAILED");
        }
        prev_state = gpio_state;
        sleep_ms(500);
    }
}

void test_read_char(){
    char result;
    //For lower case letters
    for (char c = 'a'; c<='z'; c++){
    result = char_inversion(c);
    TEST_ASSERT_TRUE_MESSAGE(result = c - 32 , "TEST FAILED");
    }
    //For Upper case letters
    for (char c = 'A'; c<='Z'; c++){
    result = char_inversion(c);
    TEST_ASSERT_TRUE_MESSAGE(result = c + 32 , "TEST FAILED");
    }
}

int main (void)
{
    stdio_init_all();
    sleep_ms(5000); // Give time for TTY to attach.
    printf("BEGIN TESTING\n");
    UNITY_BEGIN();
    RUN_TEST(test_read_char);
    RUN_TEST(test_led_pin);
    sleep_ms(5000);
    return UNITY_END();
}