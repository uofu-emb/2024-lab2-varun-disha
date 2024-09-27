#ifndef MAIN_FUNCTIONS_H
#define MAIN_FUNCTIONS_H

typedef struct {
    bool on;
    int count;
} LedBlinkResult;

char char_inversion(char c);
LedBlinkResult led_blink(bool on, int count);

#endif