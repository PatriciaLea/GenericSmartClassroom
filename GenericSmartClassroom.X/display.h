#ifndef __DISPLAY_H_
#define	__DISPLAY_H_

#define F_CPU 16000000UL
#include <util/delay.h> // include processor files - each processor file is guarded.  
#include <avr/io.h>

// Pins & Marcros
#define SPI_DDR DDRB
#define CS      PINB2 //ChipSelect/SlaveSelect
#define MOSI    PINB3 //MasterInSlaveOut
#define SCK     PINB5 //SerialClocK
#define D_C     PIND2 //Data Command
#define Reset   PIND3

void SPI_init(void);

void SPISend8Bit(uint8_t);
void Display_init(void);

#endif