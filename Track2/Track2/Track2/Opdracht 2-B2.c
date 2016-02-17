/*
 * Track2.c
 *
 * Created: 17-2-2016 11:10:20
 * Author : aares
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int number;
void wait(int ms)
{
	for(int i = 0; i < ms; i++)
	{
		_delay_ms(1);
	}
}

ISR(INT1_vect)
{
	number = number<<1;
	if(number > 0b10000000)
	{
		number = 0b00000001;
	}
	PORTB = number;
	wait(500);
}

ISR(INT2_vect)
{
	number = number<<1;
	if(number > 0b10000000)
	{
		number = 0b00000001;
	}
	PORTB = number;
	wait(500);
}

void execInter()
{
	EICRA |= 0b11111111;
	EIMSK |= 0b00000110;
	sei();
}

int main(void)
{
	number = 0b00000001;
    DDRB = 0b11111111;
	DDRD = 0b11110000;
	PORTB = number;
	execInter();
    while (1) 
    {
    }
	return 1;
}

