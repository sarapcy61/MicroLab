#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/interrupt.h>


volatile uint8_t total_overflow = 0;
volatile int counter = 0;
volatile bool clockwise = true;

char cycles[] = {0x09, 0x05, 0x06, 0x0A};

ISR(TIMER0_OVF_vect)
{
    total_overflow++;
}

int main(void)
{
    TCCR0 |= (1 << CS01) | (1 << CS00);
    TCNT0 = 0;
    TIMSK |= (1 << TOIE0);
    sei();

    DDRB = 0x0F;
    PORTB = 0x00;

    DDRA = 0x01;
    PORTA = 0x04;

    while (1)
    {
        if (!clockwise) {
            PORTA |= (1 << 0);
        } else {
            PORTA &= ~(1 << 0);
        }

        if (!(PINC & (1 << 2)))
        {
            clockwise = !clockwise;
            while (!(PINC & (1 << 2)));
        }

        if (total_overflow >= 61)
        {

            TCNT0 = 0;
            while (TCNT0 <= 9);

            PORTB cycles[counter];

            TCNT0 = 0;
            total_overflow = 0;

            !clockwise ? counter-- : counter++;

            if (counter >= 4)
            {
                counter = 0;
            }

            if (counter <= -1)
            {
                counter = 3;
            }
        }
    }
}

