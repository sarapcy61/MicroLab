#include <avr/io.h>
#include <avr/pgmspace.h>
#define F_CPU 1000000UL

unsigned char display[10] PROGMEM = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

void timer1_init()
{

}

void timer0_init()
{

}

int main(void)
{
    DDRD = 0xff;
    DDRC = 0x0f;

    unsigned int first = 0;
    unsigned int second = 0;
    unsigned int third = 0;
    unsigned int fourth = 0;

    unsigned int counter = 1;

    PORTC = ~counter;

    TCCR1B |= (1 << CS11) | (1 << CS10);
    TCNT1 = 0;

    TCCR0 |= (1 << CS00) | (1 << CS01);
    TCNT0 = 0;

    while (1) {
        if (TCNT0 >= 155) {
            if (counter < 8) {
                counter = counter << 1;
                PORTC = ~(counter);
            }
            else {
                counter = 0x01;
                PORTC = ~(counter);
            }

            PORTD = pgm_read_byte(&(display[3]));

            if (counter & 1){
                PORTD = pgm_read_byte(&(display[first]));
            }

            else if (counter & 2){
                PORTD = pgm_read_byte(&(display[second]));
            }

            else if (counter & 4){
                PORTD = pgm_read_byte(&(display[third]));
            }

            else if (counter & 8){
                PORTD = pgm_read_byte(&(display[fourth]));
            }

            TCNT0 = 0;
        }

        if (TCNT1 >= 7000){
            first++;
            second += first / 10;
            first = first % 10;

            third += second / 10;
            second = second % 10;

            fourth += third / 10;
            third = third % 10;

            if (fourth == 9 & third == 9 & second == 9 & first == 9) {
                first = 0;
                second = 0;
                third = 0;
                fourth = 0;
            } 

            TCNT1 = 0;
        }
    }
}