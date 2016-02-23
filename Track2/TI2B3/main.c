/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** lookup.c
**
** Beschrijving:	Ledpatroon op PORTD dmv table lookup (scheiding logica en data)    
** Target:			AVR mcu
** Build:			avr-gcc -std=c99 -Wall -O3 -mmcu=atmega128 -D F_CPU=8000000UL -c switch.c
**					avr-gcc -g -mmcu=atmega128 -o lookup.elf lookup.o
**					avr-objcopy -O ihex lookup.elf lookup.hex 
**					or type 'make'
** Author: 			dkroeske@gmail.com
** -------------------------------------------------------------------------*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/******************************************************************/
void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

const unsigned char
NUMBERS[16] =
{
0b00111111, // 0
0b00000110, // 1
0b01011011, // 2
0b01001111, // 3
0b01100110, // 4
0b01101101, // 5
0b01111101, // 6
0b00000111, // 7
0b01111111, // 8
0b01101111,
0b01110111, // A
0b01111100, // b
0b00111001, // C
0b01011110, // d
0b01111001, // E
0b01110001 // F
};

int currentNumber;

ISR( INT4_vect )
{
	currentNumber++;
	wait(100);
}

ISR( INT5_vect )
{
	currentNumber--;
	wait(100);
}

int main( void )
{
	currentNumber = 0;
	DDRD = 0b11111111;					// PORTD all output
	DDRE = 0b00000000;					// PORTE all input 
	
	EICRB |= 0b000001010;
	EIMSK |= 0b000110000;
	sei();

	while(1)
	{
		if(currentNumber < 0 || currentNumber > 15)
		{
			PORTD = NUMBERS[14];
		}
		else
		{
			PORTD = NUMBERS[currentNumber];
		}
		wait(1000);
	}
	return 1;
}
