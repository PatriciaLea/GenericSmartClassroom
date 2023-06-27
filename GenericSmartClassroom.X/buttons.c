#include <avr/io.h>
#include <avr/interrupt.h>

#define BUTTON_PIN      PD4 //PCINT20
#define BUTTON2_PIN     PC1 //PCINT9
#define BUTTON3_PIN     PB0 //PCINT0

#define BUTTON_PRESSED  !(PIND & (1 << BUTTON_PIN))
#define BUTTON2_PRESSED  !(PINC & (1 << BUTTON2_PIN))
#define BUTTON3_PRESSED  !(PINB & (1 << BUTTON3_PIN))

void init_Button(void){
    
    //LED Gelb
    DDRB |= (1<<DDB4); //PIN B4 is output
    PORTB |= ~(1<<PORTB4); // low
    
    DDRD |= (1<<DDD7);
    PORTD |= ~(1<<PORTD7);
    
    
    // Set BUTTON_PIN as input with pull-up resistor
    
    //Button 1
    DDRD &= ~(1 << BUTTON_PIN); //set Button Pin as input
    PORTD |= (1 << BUTTON_PIN); //set pull up

    //Button 2
    DDRC &= ~(1 << BUTTON2_PIN); //set Button2 Pin as input
    PORTC |= (1 << BUTTON2_PIN); // set pull up
    
    //Button 3
    DDRB &= ~(1 << BUTTON3_PIN); //set Button3 Pin as input
    PORTB |= (1 << BUTTON3_PIN); // set pull up
    
    //On Inputchange interrupt activated
    PCMSK2 |= (1<<PCINT20);
    PCMSK1 |= (1<<PCINT9);
    PCMSK0 |= (1<<PCINT0);
    
    PCICR |= (1<<PCIE2);
    PCICR |= (1<<PCIE1);
    PCICR |= (1<<PCIE0);
    
    OCR0A = 250;
    
    TCCR0A |= (1<<WGM01);
    
    TCCR0B |= (0b11);//set prescaler to 64 and start
    
}

ISR(PCINT2_vect){
            TCCR0B |= (0b11);//set prescaler to 64 and start
}

ISR(PCINT1_vect){
            TCCR0B |= (0b11);//set prescaler to 64 and start
}

ISR(PCINT0_vect){
            TCCR0B |= (0b11);//set prescaler to 64 and start
}

ISR(TIMER0_OVF_vect){
    if(BUTTON_PRESSED){
        PORTB ^= (1<<PORTB4);
    }
    else if(BUTTON2_PRESSED){
        servo();
    }
    else if(BUTTON3_PRESSED){
        
    }
}
