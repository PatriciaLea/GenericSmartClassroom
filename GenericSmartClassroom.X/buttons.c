#include <avr/io.h>
#include <avr/interrupt.h>

#define BUTTON_PIN      PD4 //PCINT20
#define BUTTON2_PIN     PC1 //PCINT9


#define BUTTON_PRESSED  !(PIND & (1 << BUTTON_PIN))
#define BUTTON2_PRESSED  !(PINC & (1 << BUTTON2_PIN))


void init_Button(void){
    
    //LED Gelb
    DDRB |= (1<<DDB4); //PIN B4 is output

    
    DDRD |= (1<<DDD7);

    
    
    // Set BUTTON_PIN as input with pull-up resistor
    
    //Button 1
    DDRD &= ~(1 << BUTTON_PIN); //set Button Pin as input
    PORTD |= (1 << BUTTON_PIN); //set pull up

    //Button 2
    DDRC &= ~(1 << BUTTON2_PIN); //set Button2 Pin as input
    PORTC |= (1 << BUTTON2_PIN); // set pull up    
    
    //On Inputchange interrupt activated
    PCMSK2 |= (1<<PCINT20);
    PCMSK1 |= (1<<PCINT9);
    
    PCICR |= (1<<PCIE2);
    PCICR |= (1<<PCIE1);
    
    TIMSK0 |= (1<<TOIE0); //allow overflow interrupt for timer0
    
    OCR0A = 250;
    sei();
}

ISR(PCINT2_vect){
    TCCR0B |= (1<< CS02) | (1<< CS00);//set prescaler to 1024 and start

}

ISR(PCINT1_vect){
    TCCR0B |= (1<< CS02) | (1<< CS00);//set prescaler to 1024 and start
}


ISR(TIMER0_OVF_vect){
    TCCR0B &= ~((1<<CS00) | (1<<CS01) | (1<<CS02)); //stop timer
    if(BUTTON_PRESSED){
        PORTB ^= (1<<PORTB4);
    }
    else if(BUTTON2_PRESSED){
        servo();
    }

}