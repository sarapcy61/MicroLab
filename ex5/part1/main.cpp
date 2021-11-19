#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t total_overflow = 0;
volatile uint8_t counter = 0;

char angels[] = {0x09, 0x05, 0x06, 0x0A};

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

    PORTC = 0x01;

    while (1)
    {
        if ((total_overflow >= 2) & !(PINA & (1 << 0)))
        {
            TCNT0 = 0;
            while (TCNT0 <= 113);

            PORTB = angels[counter];

            TCNT0 = 0;
            total_overflow = 0;

            counter++;

            if (counter >= 4)
            {
                counter = 0;
            }
        }
    }
}

