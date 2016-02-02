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
    /* Replace with your application code */
    while (1) 
    {
		PORTD = 0b10000000;
		PORTD = 0b01000000;
		wait(5000);
		PORTD = 0b01000000;
		PORTD = 0b10000000;
		wait(5000);
    }
	return 1;
}

