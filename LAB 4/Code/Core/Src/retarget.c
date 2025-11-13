#include "main.h"
#include <stdio.h>

/* The UART handle lives in main.c in single-file init projects */
extern UART_HandleTypeDef huart1;   // change to huart2 if you enabled USART2

int __io_putchar(int ch) {
    uint8_t c = (uint8_t)ch;
    HAL_UART_Transmit(&huart1, &c, 1, HAL_MAX_DELAY);
    return ch;
}

int _write(int file, char *ptr, int len) {
    for (int i = 0; i < len; i++) __io_putchar(ptr[i]);
    return len;
}
