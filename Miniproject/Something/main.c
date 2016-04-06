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

void twi_clear3(void)
{
	//for(int i = 0; i < 15; i += 2)
	//{
		twi_start();
		twi_tx(0xE0);	// Display I2C addres + R/W bit
		twi_tx(0x00);	// Address
		twi_tx(0xAF);	// data
		twi_tx(0x00);	
		twi_tx(0x55);	// data
		twi_tx(0x00);
		twi_tx(0x77);	// data
		twi_tx(0x00);
		twi_tx(0x44);	// data
		twi_tx(0x00);
		twi_tx(0x22);	// data
		twi_tx(0x00);
		twi_tx(0x22);	// data
		twi_tx(0x00);
		twi_tx(0x22);	// data
		twi_tx(0x00);
		twi_tx(0x22);	// data
		twi_stop();
	//}
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

	// Init HT16K22. Page 32 datasheet
	twi_start();
	twi_tx(0xE0);	// Display I2C addres + R/W bit
	twi_tx(0x21);	// Internal osc on (page 10 HT16K33)
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C address + R/W bit
	twi_tx(0xA0);	// HT16K33 pins all output
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C address + R/W bit
	twi_tx(0xE3);	// Display Dimming 4/16 duty cycle
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C address + R/W bit
	twi_tx(0x81);	// Display OFF - Blink On
	twi_stop();

	while (1)
	{
		twi_clear3();
		//twi_start();
		//twi_tx(0xE0);	// Display I2C addres + R/W bit
		//twi_tx(0x02);	// Address
		//twi_tx(0x0b00000000);	// data
		//twi_stop();	
//
		//twi_start();
		//twi_tx(0xE0);	// Display I2C addres + R/W bit
		//twi_tx(0x00);	// Address
		//twi_tx(0x0b00000000);	// data
		//twi_stop();
//
		twi_start();
		twi_tx(0xE0);
		twi_tx(0x00);
		for(int i = 0; i < 16; i++)
		{
			twi_tx(0x00);
		}
		twi_stop();
		//wait(500);
	}

	return 1;
}