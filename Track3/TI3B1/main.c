/*
 * TI3B1.c
 *
 * Created: 23-2-2016 12:31:44
 * Author : titat_000
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "lcd.h"

int main(void)
{
	DDRC = 0b11111111;

	char sampleString[] = "This is a sample string";

	lcd_init();
	display_text(sampleString,0);

    while (1) 
    {
		lcd_scrollRight();
		_delay_ms(3000);   
    }
}

