#include <avr/io.h>
#include <util/delay.h>

typedef struct { 
	unsigned char data;
	unsigned int delay ;
} PATTERN_STRUCT; 

PATTERN_STRUCT pattern[] = { 
	{0b000000001, 500}, 
	{0b000000010, 500}, 
	{0b000000100, 500},
	{0b000001000, 500},
	{0b000010000, 500},
	{0b000100000, 500},
	{0b001000000, 500},
	{0b010000000, 500},
	{0b001000000, 500},
	{0b000100000, 500},
	{0b000010000, 500},
	{0b000001000, 500},
	{0b000000100, 500},
	{0b000000010, 500}, 
	{0b000000001, 500}
};

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

int main( void )
{
	DDRD = 0b11111111;					// PORTD all output 
	int index = 0;

	while (1)
	{
		// Set index to begin of pattern array
		
		
		if(index > sizeof(pattern))
		{
			index = 0;
		}
		else
		{
			PORTD = pattern[index].data;
			// wait
			wait(pattern[index].delay);
			// increment for next round
			index++;
		}
	}

	return 1;
}