/*
 * ADC 1.c
 *
 * Created: 3/29/2022 1:42:07 PM
 * Author : Eyad
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
int main (void)
{
	DDRB = 0xFF;//make Port B an output
	DDRD = 0xFF; //make Port D an output
	ADCSRA= 0x87;//make ADC enable and select ck/128
	ADMUX= 0x40;
	while(1)
	{
		ADCSRA |= (1<<ADSC);//start conversion
		while((ADCSRA&(1<<ADIF))==0);//wait for conversion to finish
		ADCSRA |= (1<<ADIF);
		PORTD = ADCL;//give the low byte to PORTD
		PORTB = ADCH;//give the high byte to PORTB
	}
}

