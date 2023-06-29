#include <xc.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#include "display.h"
#include "tft.h"
#include "spi.h"
#include "picture.h"

uint16_t Bildschirm[6] = {
	0xEF00,
	0x1805,
	0x1283,
	0x1500,
	0x1300,
	0x16AE
};

U16 InitData[] ={
		//Initialisierungsdaten fuer 16Bit-Farben-Modus
		0xFDFD, 0xFDFD,
		//pause
		0xEF00, 0xEE04, 0x1B04, 0xFEFE, 0xFEFE,
		0xEF90, 0x4A04, 0x7F3F, 0xEE04, 0x4306, //0x7F3F 
		//pause
		0xEF90, 0x0983, 0x0800, 0x0BAF, 0x0A00,
		0x0500, 0x0600, 0x0700, 0xEF00, 0xEE0C,
		0xEF90, 0x0080, 0xEFB0, 0x4902, 0xEF00,
		0x7F01, 0xE181, 0xE202, 0xE276, 0xE183,
		0x8001, 0xEF90, 0x0000
	};

void SPI_init(){
    //set Cs, MOSI and Sck to output
    SPI_DDR |= (1 << CS) | (1 << MOSI) | (1 << SCK);
    
    //enable SPI, set as master and clock to 4Mhz
    SPCR = (1 << SPE) | (1 << MSTR) | (1 <MOSI);
}

void SPISend8Bit(uint8_t data){
    PORTB &= ~(1 << CS);            //CS low
    SPDR = data;                    //load Data into Register
    while(!(SPSR & ( 1 << SPIF)));  //wait til done 1 << 7 = 0b1 & SPSR 0 solange undone. Nach Senden wird bit 7 1
    PORTB |= (1 << CS);             //CS high
}


void Display_init(void) {
    DDRD |= (1<<D_C) | (1 << Reset);    //output: Data/Command; PD3 Reset

	_delay_ms(300);
	PORTD &= ~(1<<Reset);	//Reset-Eingang des Displays auf Low => Beginn Hardware-Reset
	_delay_ms(75);
	PORTB |= (1<<CS);		//SSEL auf High
	_delay_ms(75);
	PORTD |= (1<<D_C);		//Data/Command auf High
	_delay_ms(75);
	PORTD |= (1<<Reset);	//Reset-Eingang des Displays auf High => Ende Hardware Reset
	_delay_ms(75);
	SendCommandSeq(&InitData[0], 2);
	_delay_ms(75);
	SendCommandSeq(&InitData[2], 10);
	_delay_ms(75);
	SendCommandSeq(&InitData[12], 23);
}


void sendColor(uint16_t color) {
    // Send the high byte
    SPISend8Bit(color >> 8);

    // Send the low byte
    SPISend8Bit(color & 0xFF);
}

void sendData(){
           
    for(uint16_t i = 0; i < 132*176; i++){
        sendColor(0xFFE0);
    }
    
    } 


void draw_test(){
   // SendCommandSeq(&InitData[0], 2);
	
	
	for (int i = 0; i <= 1515; i++){
		if (newProject[i] == newProject[i+1]){
			SPISend8Bit(newProject[i]);

			for (int j=0; j <= newProject[i+1]; j++){
				SPISend8Bit(newProject[i]);
			}
			i += 1;
			
			}else{
			SPISend8Bit(newProject[i]);
		}
		
	}
}
