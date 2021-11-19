#include <avr/io.h>
#define F_CPU 1000000UL

unsigned char nums[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

int main(void)
{
    DDRC = 0xff;
    DDRD = 0x0f;

    unsigned int SS1 = 0;
    unsigned int SS2 = 0;
    unsigned int SS3 = 0;
    unsigned int SS4 = 0;

    unsigned int counter = 1;

    PORTD = ~counter;

    TCCR1B |= (1 << CS11) | (1 << CS10);
    TCNT1 = 0;

    TCCR0 |= (1 << CS00) | (1 << CS01);
    TCNT0 = 0;

    while (1) {
        if (TCNT0 >= 155) {
            if (counter < 8) {
                counter = counter << 1;
                PORTD = ~(counter);
            }
            else {
                counter = 0x01;
                PORTD = ~(counter);
            }

            PORTC = nums[3];

            if (counter & 1){
                PORTC = nums[SS1];
            }

            else if (counter & 2){
                nums[SS2];
            }

            else if (counter & 4){
                nums[SS3];
            }

            else if (counter & 8){
                nums[SS4];
            }

            TCNT0 = 0;
        }

        if (TCNT1 >= 7000){
            SS1++;
            SS2 += SS1 / 10;
            SS1 = SS1 % 10;

            SS3 += SS2 / 10;
            SS2 = SS2 % 10;

            SS4 += SS3 / 10;
            SS3 = SS3 % 10;

            if (SS4 == 9 & SS3 == 9 & SS2 == 9 & SS1 == 9) {
                SS1 = 0;
                SS2 = 0;
                SS3 = 0;
                SS4 = 0;
            } 

            TCNT1 = 0;
        }
    }
}