#define F_CPU 1000000UL

#include <avr/io.h>


unsigned char display[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

int main(void)
{
    DDRC = 0xff;

    TCCR1B |= (1 << CS11);
    TCCR1B |= (1 << CS10);
    TCNT1 = 0;
    
    int digit=0;
    PORTC = pgm_read_byte(&(display[digit]));  

    while(true)
    {   
        if (TCNT1 >= 7000) {
            digit++;
            PORTC = display[digit % 10];   
            TCNT1 = 0;             
        }    
    }
}