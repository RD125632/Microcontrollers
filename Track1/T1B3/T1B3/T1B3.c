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
		if(PINC & 0x01)
		{
			PORTD = 0x80;
			wait(3);		
		}	
		else
		{
			PORTD = 0x00;
			wait(3);	
		}		
	}

	return 1;
}
