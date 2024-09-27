#include <pico/stdlib.h>
#include <pico/cyw43_arch.h>
#include "main_functions.h"

char char_inversion(char c){
    if (c <= 'z' && c >= 'a') putchar(c - 32);
    else if (c >= 'A' && c <= 'Z') putchar(c + 32);
    else putchar(c);
    return c;
}

LedBlinkResult led_blink(bool on, int count){
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, on);
    if (count++ % 11) on = !on;
    LedBlinkResult result = {on, count};
    return result;
}