#include <avr/io.h>
#include <avr/interrupt.h>
int main(void)
{
      DDRB=1<<5;
	  PORTD=1<<2;
	  EICRA=0X2;
	  EIMSK=(1<<INT0);
	  sei();
	  while(1);
	  
}
ISR (INT0_vect)
{
	PORTB^=(1<<5);
}
