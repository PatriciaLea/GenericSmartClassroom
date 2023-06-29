#ifndef UART_SEND_H
#define UART_SEND_H

#include <xc.h>

typedef enum {
    LIGHT_IN,
    LIGHT_OUT,
    TEMP,
    STATUS_LIGHT,
    STATUS_BLINDS,
    OPEN_BLINDS
} Type;

void UART_Init(uint16_t ubrr);
void UART_Transmit(Type type, uint16_t data);

#endif
