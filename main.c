/*
 * Assignment 1 (toggle 2 LEDs with 2 switches).c
 *
 * Created: 3/8/2022 12:11:50 AM
 * Author : Eyad
 */ 
#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    DDRB = 0b11111100;
    while (1) 
    {
		if((PINB & (0b00000001)) == 1){
			PORTB = 0b00000100; // turn yellow LED ON, turn red LED OFF
		}
		else if((PINB & (0b00000010)) == 2){
			PORTB = 0b00001000; // turn yellow LED OFF, turn red LED ON
		}
    }
}

