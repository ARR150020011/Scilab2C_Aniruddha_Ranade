/*
 * led_switch_001.c
 *
 * Created: 25-03-2016 00:16:33
 * Author : Aniruddha Ranade
 */ 

#include <avr/io.h>
#define bit_is_clear(sfr,bit)  ((_SFR_BYTE(sfr) & _BV(bit)))
int main(void)
{
    DDRB|=(1<<PINB0);		//PINB0 FOR OUTPUT
	  DDRC&=~(1<<PINC0);		//PINC0 TO SWITCH INPUT 
    while (1) 
    {
    		if(bit_is_clear(PINC,1))
    		{
    			PORTB=0x01;		//THE LED IS ON WHEN THE SWITCH IS PRESSED (HIGH)
    		}
    		else
    		{
    			PORTB=0x00;		//THE LED IS OFF WHEN THE SWITCH IS RELEASED (LOW)
    		}	
    }
}

