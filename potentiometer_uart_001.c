/*
 * potentiometer_uart_001.c
 *
 * Created: 23-03-2016 18:45:34
 * Author : Aniruddha Ranade
 */ 

#include <avr/io.h>
#define F_CPU 1000000UL
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE ((F_CPU/(USART_BAUDRATE*16UL))-1)
#include <avr/interrupt.h>
#include <stdlib.h>

void usart_init()
{
	UBRRH=BAUD_PRESCALE;					//
	UBRRL=(BAUD_PRESCALE>>8);				//
	UCSRB=(1<<TXEN)|(1<<RXEN);				//ENABLE TRANSMITER AND RECIEVER
	UCSRC=(1<<URSEL)|(3<<UCSZ0)|(1<<USBS);	//FORMAT 8 DATA BYTES AND 2 STOP BITS
}

void transmit_string_UART(char *buffer)
{
  	uint16_t i = 0;
  	while(buffer[i] != '\0')				//LOOP THROUGH THE DATA
  	{
    	while ( !(UCSRA & (1<<UDRE)) );		//TRANSMIT
    	UDR = buffer[i];
		i++;	
	}
}

int main(void)
{
	DDRA=0x00;			//PORTA FOR INPUT
	usart_init();		//USART INTIALIZATION
	//CONFIGURE ADC
	ADCSRA|=(1<<ADIE);	//ENABLE ADC INTERUPPT
	//10 BIT RESULT
	ADMUX|=(1<<REFS0);	//THE UPPER LIMIT
	ADCSRA|=(1<<ADPS2);	//ENABLE PRESCALAR == 16
	ADCSRA|=(1<<ADEN);	//TURN ON THE ADC
	sei();				//ENABLE GLOBAL INTERRUPTS
	ADCSRA|=(1<<ADSC);	//START THE CONVERSION
	while (1) 
    {
    }
}

ISR(ADC_vect)			//INTERUPPT ROUTINE
{
	char adcResult[3];	
	//itoa(ADCH , adcResult , 10);	//CONVERT THE ADC RESULT
	adcResult[0]=ADCL;
	adcResult[1]=ADCH;
	transmit_string_UART(adcResult);//SEND DATA TO PC THROUGH UART
	ADCSRA|=(1<<ADSC);				//START NEXT CONVERSION
}


