#define F_CPU 16000000UL

#include <xc.h>
#include <util/delay.h>

#include "buttons.h"
#include "sensors.h"
#include "servo.h"
#include "spi.h"
#include "tft.h"

#include "uartSend.h"

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
    
    while (1) {
        //Send data repeatedly, testdata test is sent 1x alle 1000ms
        UART_Transmit('t');
        _delay_ms(1000);
        
        //to do send data to display
    }
}


//Zwischenablage, sorry :D
const uint8_t testImage[] = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0x00, 0x11, 0x00, 0x11, 0x00, 0x11, 0x00, 0x11, 0x00, 0x11, 0x00, 0x11, 0x00, 0x11, 0x00, 0x11, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0x00, 0x11, 0xff, 0xff, 0x00, 0x11, 0x00, 0x11, 0x00, 0x11, 0x00, 0x11, 0xff, 0xff, 0x00, 0x11, 0xff, 0xff, 
0xff, 0xff, 0x00, 0x11, 0xff, 0xff, 0x00, 0x11, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x11, 0xff, 0xff, 
0xff, 0xff, 0x00, 0x11, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x11, 0xff, 0xff, 0x00, 0x11, 0xff, 0xff, 
0xff, 0xff, 0x00, 0x11, 0xff, 0xff, 0x00, 0x11, 0x00, 0x11, 0x00, 0x11, 0xff, 0xff, 0xff, 0xff, 0x00, 0x11, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x11, 0xff, 0xff, 
0xff, 0xff, 0x00, 0x11, 0x00, 0x11, 0x00, 0x11, 0x00, 0x11, 0x00, 0x11, 0x00, 0x11, 0x00, 0x11, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};