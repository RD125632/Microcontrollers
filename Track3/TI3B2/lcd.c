#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "lcd.h"

// Send a command to LCD
void lcd_command(unsigned char dat)
{
	PORTC = dat & 0XF0;     // top nibble
	PORTC = PORTC | 0x08;   // data (RS=0)
	// start (EN=1)
	_delay_ms(1);               // Wait 1 ms
	PORTC = 0x04;           // stop (EN=0)

	PORTC = (dat & 0x0F) << 4;  // Down nibble
	PORTC = PORTC | 0x08;       // data (RS=0)
	// start (EN=1)
	_delay_ms(1);                   // Wait 1 ms
	PORTC = 0x00;               // stop(EN=0, RS=0)
	              // wait 15 ms for command delay
}

// Set cursor position
void set_cursor(int position)
{
	int cursorPos = position;

	if(cursorPos > 16)
	{
		lcd_setLine(2);
		cursorPos -= 16;
	}
	else
	{
		lcd_setLine(1);
	}

	for(int i = 1; i < cursorPos; i++)
	{
		lcd_command(shiftCursor);
	}
}

// Write a single char to LCD
void lcd_writeChar(unsigned char dat )
{
	PORTC = dat & 0XF0;     // top nibble
	PORTC = PORTC | 0x0C;   // data (RS=1)
	// start (EN=1)
	_delay_ms(1);               // Wait 1 ms
	PORTC = 0x04;           // stop (EN=0)

	PORTC = (dat & 0x0F) << 4;  // Down nibble
	PORTC = PORTC | 0x0C;       // data (RS=1)
	// start (EN=1)
	_delay_ms(1);                   // Wait 1 ms
	PORTC = 0x00;               // stop(EN=0, RS=0)
	_delay_ms(15);              // wait 15 ms for command delay
}

void lcd_clear()
{
	lcd_command( 0x01 );    // Clear
	_delay_ms(15);
}

// Set line to write
void lcd_setLine(int row)
{
	switch (row)
	{
		case 0: lcd_command(0x80);      // Position on row 1 col 1
		case 1: lcd_command(0x80);      // Position on row 1 col 1
		case 2: lcd_command(0xC0);      // Position on row 2 col 1
		default : lcd_command(0x80);	// Position on row 1 col 1
	}	   
}

// Write characters
void display_text(char text[], int row)
{
	int size = arraySize(text);
	if(size > 16)
	{
		for(int index = 1; index < 3; index++)
		{
			lcd_setLine(index);
			for (int i = 0; i < 16; i++)
			{
				lcd_writeChar((unsigned char)text[i]);
			}
		}
	}
	else
	{
		lcd_setLine(row);
		for (int i = 0; i < 16; i++) {
			lcd_writeChar(text[i]);
		}
	}




}

// Scroll Text to right
void lcd_scrollRight()
{
	lcd_command(0x18);
}

// Scroll Text to Left
void lcd_scrollLeft()
{
	lcd_command(0x1c);
}

// Initialisation
void lcd_init()
{
	_delay_ms(400);         // wait 300 ms for initialisation
	lcd_command( 0x02 );    // return home
	_delay_ms(15);
	lcd_command( 0x28 );    // set mode to: 4 bits interface data, 2 lines, 5x8 dots
	_delay_ms(15);
	lcd_command( 0x0C );    // display: on, cursor off, blinking off
	_delay_ms(15);
	lcd_command( 0x06 );    // entry mode: cursor to right, no shift
	_delay_ms(15);
	lcd_command( 0x80 );    // RAM address: 0, first position, line 1
	_delay_ms(15);
	lcd_command( 0x01 );    // Clear
	_delay_ms(100);         // wait 100 ms
}