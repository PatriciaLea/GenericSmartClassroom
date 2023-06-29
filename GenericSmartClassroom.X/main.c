#define F_CPU 16000000UL
#include <xc.h>
#include <util/delay.h>

#include "buttons.h"
#include "sensors.h"
#include "servo.h"

#include "spi.h"
#include "tft.h"

#include "uartSend.h"
#include "uartReceive.h"

#include "display.h"

#define BAUDRATE 9600
#define UBRRVAL ((F_CPU/16/BAUDRATE)-1)




void init_Master(){
    init_Button();
    init_ADC();
    init_Servo();
    UART_Init(UBRRVAL);
    SPI_init();
    Display_init(); 
}

void main(void) {
    
    init_Master();
    drawScreen(30, 10);
    
    while (1) {
        //Send data repeatedly, testdata test is sent 1x alle 1000ms
        UART_Transmit(LIGHT_IN, getLightIn());
        _delay_ms(100);
        
        UART_Transmit(LIGHT_OUT, getLightOut());
        _delay_ms(100);
        
        UART_Transmit(TEMP, getTemp());
        _delay_ms(100);
               
        //UART_Transmit(STATUS_LIGHT, );
        //UART_Transmit(STATUS_BLINDS, ());
        

        
        

    }
}
