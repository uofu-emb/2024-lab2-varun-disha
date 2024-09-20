#include <stdio.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <unity.h>
#include "unity_config.h"
#include "pico/cyw43_arch.h"
//#include "blink.h"

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

char read_char(char c){
    if (c <= 'z' && c >= 'a') putchar(c - 32);
    else if (c >= 'A' && c <= 'Z') putchar(c + 32);
    else putchar(c);
    return c;
}

void led_pin(){
    int count = 0;
    bool on = false;    
    int gpio_state = false;
    int check_count = 0;

    //Testing 10 times as 110 is multiple of 11 and checking how many times it enters the loop to verify.
    for(int loop_count = 0; loop_count <111; loop_count ++)
    {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, on);
        gpio_state = cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN);
        TEST_ASSERT_EQUAL_MESSAGE(gpio_state, on, "TEST FAILED");
        if(count++ % 11){
            check_count++;
            on = !on;
        }
        sleep_ms(500);
    }
    TEST_ASSERT_EQUAL_MESSAGE(check_count, 100, "TEST FAILED");
}

void test_read_char(){
    char result;
    //For lower case letters
    for (char c = 'a'; c<='z'; c++){
    result = read_char(c);
    TEST_ASSERT_TRUE_MESSAGE(result = c - 32 , "TEST FAILED");
    }
    //For Upper case letters
    for (char c = 'A'; c<='Z'; c++){
    result = read_char(c);
    TEST_ASSERT_TRUE_MESSAGE(result = c + 32 , "TEST FAILED");
    }
}

void test_led_pin(){
    sleep_ms(5000);
}


int main (void)
{
    stdio_init_all();
    sleep_ms(5000); // Give time for TTY to attach.
    printf("Start tests\n");
    UNITY_BEGIN();
    // RUN_TEST(test_variable_assignment);
    // RUN_TEST(test_multiplication);
    RUN_TEST(test_read_char);
    //RUN_TEST(led_pin);
    sleep_ms(5000);
    return UNITY_END();
}