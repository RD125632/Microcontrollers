/*
 * bullshit.c
 *
 * Created: 2-2-2016 12:01:56
 * Author : aares
 */ 

#include <avr/io.h>
#include <util/delay.h>

void wait(int ms)
{
		for(int i = 0; i < ms; i++)
	{
		_delay_ms(1);
	}
	
}

int main(void)
{
	DDRD = 0b11111111;
	int shift = 0b00000001; 
    while (1) 
    {
		PORTD = shift;
		shift = shift<<1;
		wait(500);
		if(shift > 0b10000000)
		{
			shift = 0b00000001;
		}
    }
	return 1;
}

