#ifndef UART_SEND_H
#define UART_SEND_H

#include <xc.h>

extern void UART_Init(uint16_t ubrr);
extern void UART_Transmit(uint16_t data);

#endif