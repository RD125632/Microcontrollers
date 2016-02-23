/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Beschrijving:	Opdracht B3 uit Track 1  
** Target:			AVR mcu
** Author: 			rcajdane@avans.nl
** -------------------------------------------------------------------------*/


#include <avr/io.h>
#include <util/delay.h>

void readPin();

/******************************************************************/
void wait( int ms )
/* 
short:			Busy wait number of millisecs
inputs:			int ms (Number of millisecs to busy wait)
outputs:	
notes:			Busy wait, not very accurate. Make sure (external)
				clock value is set. This is used by _delay_ms inside
				util/delay.h
Version :    	DMK, Initial code
*******************************************************************/
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}
int speed = 500;

/******************************************************************/
int main( void )
/* 
short:			main() loop, entry point of executable
inputs:			
outputs:	
notes:			Looping forever, flipping bits on PORTD
Version :    	DMK, Initial code
*******************************************************************/
{
	
	DDRD = 0b11111111;			// All pins PORTD are set to output 
	PORTC = 0x10;

	while (1)
	{
		readPin();

		PORTD = 0b10000000;
		PORTD = 0b01000000;
		wait(speed);
		PORTD = 0b01000000;
		PORTD = 0b10000000;
		wait(speed);
	}


	return 1;
}


void readPin()
{
		if(PINC & 0x01)
		{
			if(speed < 4000)
			{
				speed = speed*2;

			}
			else
			{
				speed = 500;
			}
		}
}
