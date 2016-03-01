/*
 * Project name:
     Demo4_5 : PWM with timer 1 Fast PWM mode at PORTB.5, PB.6 en PB.7
	 			parallel, 3x, for RGB LED
 * Author: Avans-TI, JW
 * Revision History: 
     20101230: - initial release;
 * Description:
     This program gives an interrupt on each ms
 * Test configuration:
     MCU:             ATmega128
     Dev.Board:       BIGAVR6
     Oscillator:      External Clock 08.0000 MHz
     Ext. Modules:    -
     SW:              AVR-GCC
 * NOTES:
     - Turn ON the PORT LEDs at SW12.1 - SW12.8
*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BIT(x)			(1 << (x))

unsigned int sCount=0, minutes=0, hours=0;

// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}

// Initialize timer 1: fast PWM at pin PORTB.6 (hundredth ms)
void timer1Init( void )
{
	OCR1A = 0;					// RED, default, off
	OCR1B = 0;					// GREEN, default, off
	OCR1C = 0;					// BLUE, default, off
	TCCR1A = 0b10101001;		// compare output OC1A,OC1B,OC1C
	TCCR1B = 0b00001011;		// fast PWM 8 bit, prescaler=64, RUN
}

// Set pulse width for RED on pin PB5, 0=off, 255=max
void setRed( unsigned char red )
{
	OCR1A = red;
}
void setGreen( unsigned char green)
 {
	OCR1B = green;
 }
void setBlue( unsigned char blue)
 {
	OCR1C = blue;
 }

void fadeOutRed( unsigned char red )
{
	if(red != 255)
	{
		setRed(red);
		wait(200);
		red++;
		fadeOutRed(red);
	}
}
void fadeInRed( unsigned char red )
{
	if(red != 0)
	{
		setRed(red);
		wait(200);
		red--;
		fadeInRed(red);
	}
}
void fadeOutGreen( unsigned char green )
{
	if(green != 255)
	{
		setGreen(green);
		wait(200);
		green++;
		fadeOutGreen(green);
	}
}
void fadeInGreen( unsigned char green )
{
	if(green != 0)
	{
		setGreen(green);
		wait(200);
		green--;
		fadeInGreen(green);
	}
}
void fadeOutBlue( unsigned char blue )
{
	if(blue != 255)
	{
		setBlue(blue);
		wait(200);
		blue++;
		fadeOutBlue(blue);
	}
}
void fadeInBlue( unsigned char blue )
{
	if(blue != 0)
	{
		setBlue(blue);
		wait(200);
		blue--;
		fadeInBlue(blue);
	}
}


// Main program: Counting on T1
int main( void )
{
	DDRB = 0xFF;					// set PORTB for compare output 
	timer1Init();
	wait(100);
			
			setGreen(255);
			setRed(255);
			setBlue(255);

	while (1)
	{
	/*
		## Opdracht TI4B2.B
		//* Set a red light and fade
		fadeInRed( 255 );
		fadeOutRed( 0 );
	
		wait(1000);
		setGreen(255);
		setRed( 255 );

		//* Set a blue light and fade
		fadeInBlue( 255 );
		fadeOutBlue( 0 );
		
		wait(1000);
		setBlue(255);
		setRed(255);
		//* Set a red light and fade
		fadeInGreen( 255 );
		fadeOutGreen( 0 );

		wait(1000);		
		*/

		/* ## Opdracht TI4B2.c  */
		for(int red = 255; red >= 0; red--)
		{
			setGreen(255 - red);
			setRed(red);
			wait(100);
		}
		
		for(int blue = 255; blue >= 0; blue--)
		{
			setRed(255 - blue);
			setBlue(blue);
			wait(100);
		}

		for(int green = 255; green >= 0; green--)
		{
			setBlue(255- green);
			setGreen(green);
			wait(100);
		}
	} 
}