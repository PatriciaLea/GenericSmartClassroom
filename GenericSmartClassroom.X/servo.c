#define F_CPU 16E6
#include <avr/io.h>

#define SERVO_PIN       PB1

void init_Servo() {
    // Set the servo pin as output
    DDRB |= (1 << SERVO_PIN);
    
    // Set Timer1 in Fast PWM mode with ICR1 as TOP
    TCCR1A |= (1 << WGM11) | (1 << COM1A1);
    TCCR1B |= (1 << WGM13) | (1 << WGM12);
    
    
    ICR1 = 40000; // for 50 Hz
    
    //Ausgansposition
    //OCR1A = 2000; //1 mils (-90 Grad)
    //OCR1A = 3000; //1.5 mils (0 Grad)
    //OCR1A = 4000; //2 mills (+90 Grad)
    
}

ISR(TIMER1_OVF_vect){
    TCCR1B &= ~(1 << CS11); //stop timer
}

void servo(){
    TCCR1B |= (1 << CS11); //start timer
    if (OCR1A == 2000){
        OCR1A = 4000;
    }
    else {
        OCR1A =2000;
    }
}
