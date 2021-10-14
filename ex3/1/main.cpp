#include <avr/io.h>
#include <avr/pgmspace.h>
#define F_CPU 1000000UL


unsigned char display[10] PROGMEM = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

int main(void)
{
    DDRD = 0xff;
    
    int counter=0;
    PORTD = pgm_read_byte(&(display[counter]));  
    
    TCCR1B |= (1 << CS11);
    TCCR1B |= (1 << CS10);
    TCNT1 = 0;

    while(true)
    {   
        if (TCNT1 >= 7000) {
            counter++;
            PORTD = pgm_read_byte(&(display[counter % 10]));   
            TCNT1 = 0;             
        }    
    }
}