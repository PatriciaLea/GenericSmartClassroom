#include <xc.h>
#include "uartSend.h"
#include "uartReceive.h"

void UART_Receive(Type type, uint16_t data) {
    
    while (!(UCSR0A & (1 << RXC0)));
    // Read the received type
    Type receivedType = (Type)UDR0;

    
    //Bekommen wir die Daten in einem rüber?
    /*while (!(UCSR0A & (1 << RXC0)));
    uint8_t lowByte = UDR0;

    while (!(UCSR0A & (1 << RXC0)));
    uint8_t highByte = UDR0;

    uint16_t receivedData = (uint16_t)((highByte << 8) | lowByte);
     */
    
    while (!(UCSR0A & (1 << RXC0)));
    uint8_t receivedData = UDR0;
    
    type = receivedType;
    data = receivedData;
    if(type == 3){
        if(data == 0){
            changeLightStatus();
        }
    }
    else if(type == 5){
        if (data == 0){
            servo();
        }
    }
}
