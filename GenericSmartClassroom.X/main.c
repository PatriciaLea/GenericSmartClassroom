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

uint8_t x1_coord = 0x6E; //110
uint8_t x2_coord = 0xA9; //169
uint8_t y1_coord = 0x0F; // 15
uint8_t y2_coord = 0x72; //114

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
        UART_Transmit(LIGHT_IN, getLightIn());
        _delay_ms(100);
        
        UART_Transmit(LIGHT_OUT, getLightOut());
        _delay_ms(100);
        
        UART_Transmit(TEMP, getTemp());
        _delay_ms(100);
               
        //UART_Transmit(STATUS_LIGHT, );
        //UART_Transmit(STATUS_BLINDS, ());
        //Display-Hintergrund weiß "färben"
        
	for(int i = 0; i < 23232; i++) {
		SPISend8Bit(0xFF);
		SPISend8Bit(0xFF);
	};
        
        TFT_Window(x1_coord, y1_coord, x2_coord, y2_coord, TFT_Landscape);
        //to do send data to display
        draw_test();
    }
}
