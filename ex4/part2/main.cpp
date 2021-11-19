#define F_CPU 1000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int s = 0;
int m = 0;
int h = 0;

void LCD_write_char(char c)
{
    PORTA = c;
    PORTB |= 0x03;
    _delay_ms(100);
    PORTB &= ~0x01;
}

void LCD_command(char c)
{
    PORTA = c;
    PORTB &= ~0x02;
    PORTB |= 0x01;
    _delay_ms(5);
    PORTB &= ~0x01;
}

void LCD_write_string(char *c)
{
    for (int i = 0; c[i] != 0; i++)
    {
        lcd_write_char(c[i]);
    }
}

void LCD_init()
{
    LCD_command(0x38);
    LCD_command(0x06);
    LCD_command(0x0E);
    LCD_command(0x01);
    LCD_command(0x80);
}

void timer_init()
{
    TCCR2 |= (1 << CS22);
    TCNT2 = 0;
}

void clock_trigger()
{
    if (++s >= 60)
    {
        s = 0;
        if (++m >= 60)
        {
            m = 0;
            if (++h >= 24)
            {
                h = 0;
            }
        }
    }
}

int main()
{
    DDRA = 0xff;
    DDRB = 0x03;

    lcd_init();
    timer_init();

    int clck_counter = 0;

    while (1)
    {
        if (TCNT2 >= 125)
        {
            clck_counter++;
            TCNT2 = 0;
        }

        if (clck_counter >= 125)
        {
            clock_trigger();
            LCD_command(0x01);
            if (h < 10)
            {
                lcd_write('0');
                lcd_write(h - '0');
            }

            else
            {
                lcd_write((h / 10) - '0');
                lcd_write((h % 10) - '0');
            }

            lcd_write(':');

            if (m < 10)
            {
                lcd_write('0');
                lcd_write(m - '0'));
            }

            else
            {
                lcd_write((m / 10) - '0');
                lcd_write((m % 10) - '0');
            }

            lcd_write(':');

            if (s < 10)
            {
                lcd_write('0');
                lcd_write(s - '0');
            }

            else
            {
                lcd_write((s / 10) - '0');
                lcd_write((s % 10) - '0');
            }
            clck_counter = 0;
        }
    }
}
