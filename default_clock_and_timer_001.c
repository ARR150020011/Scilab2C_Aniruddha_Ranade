/*
 * default_clock_and_timer_001.c
 *
 * Created: 22-03-2016 23:26:26
 * Author : Aniruddha Ranade
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL					         //SET THE INTERNAL CLOCK TO 8MHz
#define OCR1A 0xF9								       //0xF9====249
#define PRESCALAR 8								       //PRESCALAR
#define F_OC1A F_CPU/(2*PRESCALAR*(1+OCR1A))	//FORMULA FOR CALCULATION OF THE FREQUENCY OF THE OUTPUT WAVE  
#include <util/delay.h>

// SQUARE WAVEFORM OF 2KHz //

int main(void)
{
   	DDRD|=(1<<PIND5);							            //OC1A OUTPUT PD5 TIMER1 
	  TCCR1A|=(1<<COM1A0); 						          //TOGGLE MODE
    TCCR1B|=(1<<CS11)|(1<<WGM12);				      //PRESCALAR 8 AND CTC MODE SELECTION WITH OCR1A AS TOP
	  while (1) 
      {
      }
}

