#ifndef __DISPLAY_H_
#define	__DISPLAY_H_
#include <avr/io.h>

// Pins & Marcros
#define SPI_DDR DDRB
#define CS      PINB2 //ChipSelect/SlaveSelect
#define MOSI    PINB3 //MasterInSlaveOut
#define SCK     PINB5 //SerialClocK
#define D_C     PIND2 //Data Command
#define Reset   PIND3

void SPI_init(void);
void Display_init(void);
void SPISend8Bit(uint8_t data);
void SendCommandSeq(const uint16_t * data, uint16_t Anzahl);
void sendData();

#endif
