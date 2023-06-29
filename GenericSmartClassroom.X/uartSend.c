#define F_CPU 16E6
#include <xc.h>
#include "uartSend.h"
#include "servo.h"
#include "sensors.h"
#include "buttons.h"
#include <util/delay.h>

void UART_Init(uint16_t ubrr) { //S.149
    //Get baud rate 
    UBRR0H = (unsigned char)(ubrr >> 8); //ubrr = USART Baud Rate Register S.162
    UBRR0L = (unsigned char)ubrr;

    //Enable transmitter and receiver
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);  

    //8 data bits, 2 stop bit
    UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}


void UART_Transmit(Type type, uint16_t data) {
     //Wait for empty transmit buffer
    while (!(UCSR0A & (1 << UDRE0)));
    
    //Send type as identifier
    UDR0 = type;
    
    //Wait for empty transmit buffer
    while (!(UCSR0A & (1 << UDRE0)));
    //data into buffer, sends data
    UDR0 = data;
}

void UART_SendData(){
            //Send data repeatedly, testdata test is sent 1x alle 1000ms
        UART_Transmit(LIGHT_IN, get_photoIn());
        _delay_ms(100);
        
        UART_Transmit(LIGHT_OUT, get_photoOut());
        _delay_ms(100);
        
        UART_Transmit(TEMP, get_temp());
        _delay_ms(100);
 
        UART_Transmit(STATUS_LIGHT, get_lightStatus());
        _delay_ms(100);
        
        UART_Transmit(STATUS_BLINDS, get_blindStatus());
        _delay_ms(100);
}
