/*
 * TI3B1.c
 *
 * Created: 23-2-2016 12:31:44
 * Author : titat_000
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void init_lcd();
void lcd_command(unsigned char);
void lcd_writeChar(unsigned char);

void wait(int ms)
{
	for(int i = 0; i < ms; i++)
	{
		_delay_ms(1);
	}
	
}

int main(void)
{
	DDRC = 0b11111111;

	init_lcd();

	lcd_writeChar(0x52);
	_delay_ms(20); // wait 10 ms
	lcd_writeChar(0x65);
	_delay_ms(20); // wait 10 ms
	lcd_writeChar(0x6D);
	_delay_ms(20); // wait 10 ms
	lcd_writeChar(0x63);
	_delay_ms(20); // wait 10 ms
	lcd_writeChar(0x30);


    /* Replace with your application code */
    while (1) 
    {
    }
}

void lcd_command(unsigned char dat)
{
	PORTC = dat & 0XF0;
	PORTC = PORTC | 0x08;

	_delay_ms(1);
	PORTC = 0x04;

	PORTC = (dat & 0x0F) << 4;
	PORTC = PORTC | 0x08;

	_delay_ms(1);
	PORTC = 0x00;
}

void lcd_writeChar( unsigned char dat )
{
	PORTC = dat & 0xF0; // hoge nibble
	PORTC = PORTC | 0x0C; // data (RS=1), // start (EN=1)
	_delay_ms(1); // wait 1 ms
	PORTC = 0x04; // stop (EN = 0)
	PORTC = (dat & 0x0F) << 4; // lage nibble
	PORTC = PORTC | 0x0C; // data (RS=1), // start (EN=1)
	_delay_ms(1); // wait 1 ms
	PORTC = 0x00; // stop // (EN=0 RS=0)
}

// Initialisatie ld
//
void init_lcd(void)
{
	_delay_ms(300); // wait 10 ms
	// return home
	lcd_command( 0x02 );
	_delay_ms(20); // wait 10 ms
	// mode: 4 bits interface data, 2 lines, 5x8 dots
	lcd_command( 0x28 );
	_delay_ms(20); // wait 10 ms
	// display: on, cursor off, blinking off
	lcd_command( 0x0C );
	_delay_ms(20); // wait 10 ms
	// entry mode: cursor to right, no shift
	lcd_command( 0x06 );
	_delay_ms(20); // wait 10 ms
	// RAM adress: 0, first position, line 1
	lcd_command( 0x80 );
	_delay_ms(200); // wait 10 ms
}
