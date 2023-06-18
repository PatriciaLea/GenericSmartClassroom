#include <xc.h>
#include "uartSend.h"

void UART_Init(uint16_t ubrr) { //S.149
    //Get baud rate 
    UBRR0H = (unsigned char)(ubrr >> 8); //ubrr = USART Baud Rate Register S.162
    UBRR0L = (unsigned char)ubrr;

    //Enable transmitter 
    UCSR0B = (1 << TXEN0);

    //8 data bits, 2 stop bit
    UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void UART_Transmit(uint16_t data) {
    //Wait for empty transmit buffer
    while (!(UCSR0A & (1 << UDRE0)));

    //data into buffer, sends data
    UDR0 = data;
}