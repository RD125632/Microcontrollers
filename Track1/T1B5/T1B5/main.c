/*
 * T1B5.c
 *
 * Created: 2-2-2016 16:01:49
 * Author : titat_000
 */ 

#include <avr/io.h>
#include <util/delay.h>


/******************************************************************/
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
		int paternDown[] = {0b10000000,0b01000000,0b00100000,0b00010000,0b00001000,0b00000100,0b00000010,0b00000001};
		
		int i = 0;
		int j = 0;
		int paternSize = sizeof(paternDown)/sizeof(paternDown[0]);


	DDRD = 0b11111111;			// All pins PORTD are set to output 
	DDRC = 0b11111111;
	
	while (1)
	{
		if(j == 0)
		{
			for(i = 0; i < paternSize; i++)
			{
				PORTD = paternDown[i];
				wait(500);		
			}
			j = 1;
		}
		else
		{
			
			for(i = paternSize - 1; i >= 0; i--)
			{
				PORTC = paternDown[i];
				wait(500);
			}
			j = 0;
		}
	}

	return 1;
}


