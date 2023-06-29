#define F_CPU 16E6
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uartSend.h"



#define setPhoto1  ADMUX = 0x42; //ADC2 PC2 
#define setPhoto2  ADMUX = 0x43; //ADC3 PC3
#define setThermi  ADMUX = 0x40; //ADC0 PC0




float valuePhoto1;
float valuePhoto2;
float value;
float R2;
char charValue;

uint16_t timer_ovf = 0;

unsigned char thermi;
unsigned char photo1;
unsigned char photo2;

unsigned char lightOn;
unsigned char b1cd;
const char temps[] = {7, 9, 12, 13, 15, 17, 19, 20, 22, 23, 24, 26, 27, 28, 29, 30, 32, 33, 34, 35};

void init_LED(void) {
    //LED

    DDRC |= (1 << DDC1); //set Pin PC1 as output
    DDRD |= (1 << DDD7); //set Pin PD7 as ouput
    DDRB |= (1 << DDB4); //set Pin PB4 as ouput
}

void init_ADC(void) {
    //ADC

    ADMUX |= (1 << REFS0);
    ADMUX &= ~(1 << REFS1); //set voltage Reference to AVCC 5V

    ADMUX &= ~(1 << MUX0);
    ADMUX |= (1 << MUX1);
    ADMUX &= ~(1 << MUX2);
    ADMUX &= ~(1 << MUX3); //set Input to ADC2 (Photo1)


    ADCSRB |= (1 << ADTS0);
    ADCSRB &= ~(1 << ADTS1);
    ADCSRB &= ~(1 << ADTS2); //set to analog comparator mode/

    ADCSRA |= (1 << ADPS2);
    ADCSRA |= (1 << ADPS1);
    ADCSRA |= (1 << ADPS0); // set ADC prescaler to 128 for 125 kHz

    ADCSRA |= (1 << ADEN); // ADC enable 

    TIMSK2 |= (1 << TOIE2); //allow overflow interrupt for timer2

    TCCR2B |= (1 << CS02) | (1 << CS00); //set prescaler to 1024 and start
    
    sei();
}

ISR(TIMER2_OVF_vect) {
    timer_ovf++;
    if (timer_ovf == 3300) {

        int i;
        for (i = 0; i < 3; i++) {
            ADCSRA |= (1 << ADSC); // start conversion adcValue
            while (!(ADCSRA & (1 << ADIF)));
            value = ADC;
            switch (ADMUX) {
                case 0x42:
                    charValue = value;
                    if (charValue > 144) {
                        photo1 = 3;
                    } else if (charValue > 112) {
                        photo1 = 2;
                    } else if (charValue > 80) {
                        photo1 = 1;
                    } else {
                        photo1 = 0;
                    }
                    setPhoto2;
                    break;
                case 0x43:
                    valuePhoto2 = value;
                    charValue = value;
                    if (charValue > 144) {
                        photo2 = 3;
                    } else if (charValue > 112) {
                        photo2 = 2;
                    } else if (charValue > 80) {
                        photo2 = 1;
                    } else {
                        photo2 = 0;
                    }
                    setThermi;
                    break;
                case 0x40:
                    value = value * (float) 5 / (float) 1024;
                    value = (float) 10000 * ((float) 5 / value - (float) 1);
                    value = log(value / (float) 10000);
                    value = (float) 1 / (value / (float) 3435 + (float) 1 / (float) 298.15)-(float) 273.15;
                    thermi = value;
                    setPhoto1;
                    break;
                default:
                    break;
            }

        }
        timer_ovf = 0;
        UART_SendData();
    }
}

char get_temp() {
    return thermi;
}

char get_photoIn() {
    return photo1;
}

char get_photoOut() {
    return photo2;
}