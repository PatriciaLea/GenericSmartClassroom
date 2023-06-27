#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define setPhoto1  ADMUX = 0x42; //ADC2 PC2 
#define setPhoto2  ADMUX = 0x43; //ADC3 PC3
#define setThermi  ADMUX = 0x40; //ADC0 PC0

float valuePhoto1;
float valuePhoto2;
unsigned char thermi;
unsigned char photo1;
unsigned char photo2;

const uint8_t temps[] ={8,10,12,14,16,18,19,21,22,24,25,26,27,29,30,31,32,33,34,35};

void init_ADC(void){
    
    //ADC
    ADMUX |= (1 << REFS0); 
    ADMUX &= ~(1 << REFS1); //set voltage Reference to AVCC 5V

    ADMUX &= ~(1 <<  MUX0);
    ADMUX |= (1 <<  MUX1);
    ADMUX &= ~(1 <<  MUX2);
    ADMUX &= ~(1 <<  MUX3); //set Input to ADC2 (Photo1)
    
    //ADMUX |= (1 << ADLAR); //set ADC result left adjusted to read only ADCH

    ADCSRB &= ~(1 <<  ADTS0);
    ADCSRB &= ~(1 <<  ADTS1);
    ADCSRB &= ~(1 <<  ADTS2); //set to free running mode/
    // or ADCSRB = 0;

    ADCSRA |= (1 << ADPS2);
    ADCSRA |= (1 << ADPS1);
    ADCSRA |= (1 <<  ADPS0); // set ADC prescaler to 128 for 125 kHz

    ADCSRA |= (1 << ADIE); // enable ADC interrrupt
    ADCSRA |= (1 << ADATE); // enable ADC Auto Trigger
    ADCSRA |= (1 << ADEN); // ADC enable
    ADCSRA |= (1 << ADSC); // start first conversionadcValue 
}

ISR(ADC_vect){
    int value;
    switch (ADMUX){
        case 0x42:
            valuePhoto1 = ADC;
            if(valuePhoto1<50){
                photo1 =0;
            }
            else if(valuePhoto1<100){
                photo1 =1;
            }
            else {
                photo1 =2;
            }
            setPhoto2;
            break;
        case 0x43:
            valuePhoto2 = ADC;
            if(valuePhoto2<50){
                photo2 =0;
            }
            else if(valuePhoto2<100){
                photo2 =1;
            }
            else {
                photo2 =2;
            }
            setThermi;
            break;
        case 0x40:
            value = ADC;
            thermi = temps[value-10];
            
            setPhoto1;
            break;
        default:
            break;
    }
    _delay_ms(10);
}

char getLightIn(void){
    return photo1;
}

char getLightOut(void){
    return photo2;
}

char getTemp(void){
    return thermi;
}