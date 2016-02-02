/*
 * T1B5.c
 *
 * Created: 2-2-2016 15:56:36
 *  Author: titat_000
 */ 

#include <avr/io.h>
#include <util/delay.h>


void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

/******************************************************************/
int main( void )
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
