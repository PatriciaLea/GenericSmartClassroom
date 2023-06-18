#include <xc.h>

#include "display.h"
#include "tft.h"
#include "spi.h"


void SPI_init(){
    //set Cs, MOSI and Sck to output
    SPI_DDR |= (1 << CS) | (1 << MOSI) | (1 << SCK);
    
    //enable SPI, set as master and clock to 4Mhz
    SPCR = (1 << SPE) | (1 <MOSI);
}

void SPISend8Bit(uint8_t data){
    PORTB &= ~(1 << CS);            //CS low
    SPDR = data;                    //load Data into Register
    while(!(SPSR & ( 1 << SPIF)));  //wait til done 1 << 7 = 0b1 & SPSR 0 solange undone. Nach Senden wird bit 7 1
    PORTB |= (1 << CS);             //CS high
}


void Display_init(void) {
    DDRD |= (1<<D_C) | (1 << Reset);    //output: Data/Command; PD3 Reset

	U16 InitData[] ={
		//Initialisierungsdaten für 16Bit-Farben-Modus
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