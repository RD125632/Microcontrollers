/*
 * TI3B1.c
 *
 * Created: 23-2-2016 12:31:44
 * Author : titat_000
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "lcd.h"
unsigned int currentNumber = 0;

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

ISR( INT4_vect )
{
	lcd_clear();
	currentNumber--;
	unsigned char c = currentNumber + '0';
	
	lcd_writeChar(c);
	wait(100);
}

ISR( INT5_vect )
{
	lcd_clear();
	currentNumber++;
	unsigned char c = currentNumber + '0';
	lcd_writeChar(c);
	wait(100);
}

int main(void)
{
	currentNumber = 0;
	DDRC = 0b11111111;					// PORTD all output
	DDRE = 0b00000000;					// PORTE all input
	
	EICRB |= 0b000001010;
	EIMSK |= 0b000110000;
	sei();

	lcd_init();

    while (1) 
    {
    }
}

