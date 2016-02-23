/*
 * TI3B3.c
 *
 * Created: 23-2-2016 12:31:44
 * Author : titat_000
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int counter;
int isHigh;
int port;
ISR(TIMER2_COMP_vect)
{
	counter++;
}

int main(void)
{
	counter = 0;
	port = 0x01;
	TIMSK = 0b10000000;
	sei();
	DDRD = 0b11111110;
	DDRB = 0xFF;
	TCCR2 = 0x04;
	TCNT2 = 0x00;
    /* Replace with your application code */
    while (1) 
    {
		if(counter > 15 && isHigh == 1)
		{
			port = 0x00;
			counter = 0;
			isHigh = 0;
		}
		else if(counter > 25 && isHigh == 0)
		{
			port = 0x02;
			counter = 0;
			isHigh = 1;
		}
		PORTB = port;
    }
}
