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

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "ledmatrix.h"

typedef struct {
	unsigned char address;
	unsigned char data ;
} PATTERN_STRUCT;

PATTERN_STRUCT pattern[] = {
	{0x00, 0b00011110}, {0x02, 0b00100001}, {0x04, 0b11010100}, {0x06, 0b11000010}, {0x08, 0b11000010}, {0x0A, 0b11010100}, {0x0C, 0b00100001}, {0x0E, 0b00011110}
};

PATTERN_STRUCT pattern2[] = {
	{0x00, 0b00011110}, {0x02, 0b00100001}, {0x04, 0b11010010}, {0x06, 0b11000100}, {0x08, 0b11000100}, {0x0A, 0b11010010}, {0x0C, 0b00100001}, {0x0E, 0b00011110}
};

void twi_data(void)
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

void twi_data2(void)
{
	twi_start();
	twi_tx(0xE0);
	for (int i = 0; i < 8; i++)
	{
		twi_tx(pattern2[i].address);
		twi_tx(pattern2[i].data);
		
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
	DDRA = 0x00;

	while (1)
	{
		wait(500);
		printf("test");
		if(PINA & 0x01)
		{
			twi_data2();
		}
		else
		{
			twi_data();
		}
	}

	return 1;
}