/*
 * B3.1.c
 *
 * Created: 1-3-2016 13:24:17
 * Author : aares
 */ 

#include <avr/io.h>
#include <avr/delay.h>

void wait(int ms)
{
	for(int i = 0; i < ms; i++)
	{
		_delay_ms(1);
	}
}

int main(void)
{
	ADCSRA = 0b111000001;
	ADMUX = 0b11000001;
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRF = 0x00;

    /* Replace with your application code */
    while (1) 
    {
		ADCSRA = 0b111000001;
		PORTA = ADCL;
		PORTB = ADCH;
		wait(100);
    }
}

