#define F_CPU 1000000

#include <avr/io.h>
#include <util/delay.h>

void LCD_write_char(char c) {
    PORTA = c;
    PORTB |= 0x03;
    _delay_ms(100);
    PORTB &= ~0x01;
}

void LCD_command(char c) {
    PORTA = c;
	PORTB &= ~0x02;
	PORTB |= 0x01;
	_delay_ms(5);
	PORTB &= ~0x01;
}

void LCD_write_string(char *c) {
    for (int i = 0; c[i] != 0; i++) {
        lcd_write_char(c[i]);
    }
}

void LCD_init() {
	LCD_command(0x38);
	LCD_command(0x06);
	LCD_command(0x0E);
	LCD_command(0x01);
	LCD_command(0x80);
}

int main() {

	LCD_init();

    DDRA = 0xff;
    DDRB = 0x03;

	LCD_write_string("hello world");
    
    while(1){}
}