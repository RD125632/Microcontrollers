/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** ledmatrix.c
**
** Beschrijving:	Simple HT16K33 Ledmatix demo.
** Target:			AVR mcu
** Build:			avr-gcc -std=c99 -Wall -O3 -mmcu=atmega128 -D F_CPU=8000000UL -c ledmatrix.c
**					avr-gcc -g -mmcu=atmega128 -o ledmatrix.elf ledmatrix.o
**					avr-objcopy -O ihex ledmatrix.elf ledmatrix.hex 
**					or type 'make'
** Author: 			dkroeske@gmail.com
** -------------------------------------------------------------------------*/
# define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "ledmatrix.h"

int index;

typedef struct {
	unsigned char address;
	unsigned char data ;
} PATTERN_STRUCT;

PATTERN_STRUCT smiley[] = { //pattern voor een blije emoticon
	{0x00, 0b00011110}, {0x02, 0b00100001}, {0x04, 0b11010100}, {0x06, 0b11000010}, {0x08, 0b11000010}, {0x0A, 0b11010100}, {0x0C, 0b00100001}, {0x0E, 0b00011110}
};

PATTERN_STRUCT downey[] = { //pattern voor een boze emoticon
	{0x00, 0b00011110}, {0x02, 0b00100001}, {0x04, 0b11010010}, {0x06, 0b11000100}, {0x08, 0b11000100}, {0x0A, 0b11010010}, {0x0C, 0b00100001}, {0x0E, 0b00011110}
};

PATTERN_STRUCT brainfart[] = { //pattern voor tripstate
	{0x00, 0x00}, {0x02, 0x00}, {0x04, 0x00}, {0x06, 0x00}, {0x08, 0x00}, {0x0A, 0x00}, {0x0C, 0x00}, {0x0E, 0x00},
	{0x00, 0b00000000}, {0x02, 0b00000000}, {0x04, 0b00000000}, {0x06, 0b00001100}, {0x08, 0b00001100}, {0x0A, 0b00000000}, {0x0C, 0b00000000}, {0x0E, 0b00000000},
	{0x00, 0b00000000}, {0x02, 0b00000000}, {0x04, 0b00011110}, {0x06, 0b00010010}, {0x08, 0b00010010}, {0x0A, 0b00011110}, {0x0C, 0b00000000}, {0x0E, 0b00000000},
	{0x00, 0b00000000}, {0x02, 0b00111111}, {0x04, 0b00100001}, {0x06, 0b00101101}, {0x08, 0b00101101}, {0x0A, 0b00100001}, {0x0C, 0b00111111}, {0x0E, 0b00000000},
	{0x00, 0b11111111}, {0x02, 0b11000000}, {0x04, 0b11011110}, {0x06, 0b11010010}, {0x08, 0b11010010}, {0x0A, 0b11011110}, {0x0C, 0b11000000}, {0x0E, 0b11111111}
};


void twi_data(PATTERN_STRUCT pattern[]) //geeft een simpele pattern weer
{
	twi_start();
	twi_tx(0xE0);
	for (int i = 0; i < 8; i++)
	{
		twi_tx(pattern[i].address);
		twi_tx(pattern[i].data);
	}
	twi_stop();
}

void twi_data_inverse(PATTERN_STRUCT pattern[]) //geeft pattern weer (inverted) nog niet getest!
{
	twi_start();
	twi_tx(0xE0);
	for (int i = 0; i < 8; i++)
	{
		twi_tx(pattern[i].address);
		twi_tx(pattern[i].data |~(0xFF));
	}
	twi_stop();
}

void twi_data3() //geeft animatie weer (brainfart pattern)
{
	twi_start();
	twi_tx(0xE0);

	for (int i = 0; i < 8; i++)
	{
		twi_tx(brainfart[i + index * 8].address);
		twi_tx(brainfart[i + index * 8].data);
	}
	index++;
	if(index > 4)
	{
		index = 3;
	}
	twi_stop();
}


/******************************************************************/
int main( void )
/* 
short:			main() loop, entry point of executable
inputs:			
outputs:	
notes:			Looping forever, trashing the HT16K33
Version :    	DMK, Initial code
*******************************************************************/
{
	twi_init();		// Init TWI interface

	twi_start();
	twi_tx(0xE0);
	twi_tx(0x00);
	for(int i = 0; i < 16; i++)
	{
		twi_tx(0x00);
	}
	twi_stop();
	DDRA = 0x00; //input open on port A
	index = 0;

	while (1)
	{
		wait(750);
		if(PINA & 0x01)
		{
			twi_data(downey);
		}
		else if(PINA & 0x02)
		{
			twi_data3();
		}
		else if(PINA & 0x04)
		{
			twi_data_inverse(smiley);
		}
		else
		{
			twi_data(smiley);
			index = 0;
		}
	}

	return 1;
}