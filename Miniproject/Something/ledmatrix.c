/*
 * ledmatrix.c
 *
 * Created: 5-4-2016 16:01:29
 *  Author: aares
 */ 

 #include <avr/io.h>
 #include <util/delay.h>
 #include "ledmatrix.h"

 /*
 TWCR:
 Bit 7 - TWINT: As described above; This is the TWI Interrupt Flag. It is set when the TWI finishes ANY bus operation and has to cleared (by writing a 1 to it) before a new operation can be started.
 Bit 6 - TWEA: TWI Enable Acknowledge; When the device receives data (as slave or as master), this bit has to be set if the next incoming byte should be ACKed and cleared for a NACK.
 Bit 5 - TWSTA: TWI Start; When a master has to generate a start condition, write this bit 1 together with TWEN and TWINT. The TWI hardware will generate a start condition and return the appropriate status code.
 Bit 4 - TWSTO: TWI Stop;
 Bit 3 - TWWC: TWI Write Collision; Set by the TWI hardware when writing to the TWI Data Register TWDR while TWINT is high.
 Bit 2 - TWEN: Any bus operation only takes place when TWEN is written to 1 when accessing TWCR.
 Bit 0 - TWIE: TWI Interrupt Enable;
 TWDR: TWI Data register
 TWBR: Bitrate register
 TWSR: Status register
 */

 void twi_init(void)
/* 
short:			Init AVR TWI interface and set bitrate
inputs:			
outputs:	
notes:			TWI clock is set to 100 kHz
Version :    	DMK, Initial code
*******************************************************************/
{
	TWSR = 0;	 // CPU clock/(16 + 2 * TWBR * (4^TWSR))
	TWBR = 32;	 // TWI clock set to 100kHz, prescaler = 0

	// Init HT16K22. Page 32 datasheet
	twi_start();
	twi_tx(0xE0);	// Display I2C addres + R/W bit
	twi_tx(0x21);	// Internal osc on (page 10 HT16K33)
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C address + R/W bit
	twi_tx(0xA0);	// HT16K33 pins all output
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C address + R/W bit
	twi_tx(0xE3);	// Display Dimming 4/16 duty cycle
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C address + R/W bit
	twi_tx(0x81);	// Display OFF - Blink On
	twi_stop();

	wait(1000);
}

/******************************************************************/
void twi_start(void)
/* 
short:			Generate TWI start condition
inputs:		
outputs:	
notes:			
Version :    	DMK, Initial code
*******************************************************************/
{
	TWCR = (0x80 | 0x20 | 0x04);
	while( 0x00 == (TWCR & 0x80) );
}

/******************************************************************/
void twi_stop(void)
/* 
short:			Generate TWI stop condition
inputs:		
outputs:	
notes:			
Version :    	DMK, Initial code
*******************************************************************/
{
	TWCR = (0x80 | 0x10 | 0x04);
}

/******************************************************************/
void twi_tx(unsigned char data)
/* 
short:			transmit 8 bits data
inputs:		
outputs:	
notes:			
Version :    	DMK, Initial code
*******************************************************************/
{
	TWDR = data;
	TWCR = (0x80 | 0x04);
	while( 0 == (TWCR & 0x80) );
}

/******************************************************************/
void wait( int ms )
/* 
short:			Busy wait number of millisecs
inputs:			int ms (Number of millisecs to busy wait)
outputs:	
notes:			Busy wait, not very accurate. Make sure (external)
				clock value is set. This is used by _delay_ms inside
				util/delay.h
Version :    	DMK, Initial code
*******************************************************************/
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}
