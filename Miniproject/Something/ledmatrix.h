/*
 * ledmatrix.h
 *
 * Created: 5-4-2016 16:05:39
 *  Author: aares
 */ 


#ifndef LEDMATRIX_H_
#define LEDMATRIX_H_

void twi_init(void);
void twi_start(void);
void twi_stop(void);
void twi_tx(unsigned char data);
void wait( int ms );

#endif /* LEDMATRIX_H_ */