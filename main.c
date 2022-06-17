/*
 * Keypad demo.c
 *
 * Created: 3/22/2022 2:32:45 PM
 * Author : Eyad
 */ 
#include <avr/io.h>
#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif
#include <util/delay.h>
#include "ALCD.h"
#define BUTTON_MASK (1<<PB4)
#define BUTTON_PIN PINB
#define BUTTON_PORT PORTB
volatile uint8_t button_down;

char key [4][4] = {
	{'1','2','3','/'},
	{'4','5','6','x'},
	{'7','8','9','-'},
	{'O','0','=','+'}
};

static inline void debounce(int Row)
{
	
	PORTC|=(1<<Row);
	static uint8_t count = 0;
	static uint8_t Last_button_state = 0;
	uint8_t current_state = (~PINC& (1<<Row)) != 0;
	if (current_state != Last_button_state)
	{         count=count+1;
		if (count >= 4) {

			Last_button_state = current_state;
			if (current_state != 0) {
				button_down = 1;
			}
			count = 0;
		}
	}
	else {
	count = 0;      }
};
char keypadscan()
{
	DDRC&=~0xFF;//rows
	DDRB&=~0xFF;//columns
	PORTC|=0xFF;
	for(int i=0;i<4;i++)
	{
		DDRB|=(1<<i);
		PORTB &=~(1<<i);
		for(int j=0;j<4;j++)
		{
			if((PINC&1<<j)==0)
			{
				debounce(j);
				while(button_down==0)
				{
					debounce(j);
				}
				return key[j][i];
				
			}
			
		}
		DDRB&=~0xFF;
	}
	return 'T';
}

int changetointger(char z)
{
	if(z=='0') return 0;
	if(z=='1') return 1;
	if(z=='2') return 2;
	if(z=='3') return 3;
	if(z=='4') return 4;
	if(z=='5') return 5;
	if(z=='6') return 6;
	if(z=='7') return 7;
	if(z=='8') return 8;
	if(z=='9') return 9;
}


int main(void)
{
	lcd_init(16);
	char z='T';
	int y=0;//input1
	int r=0;//input2
	char o;//operator (+,-,/,x)
	char k[16];//char output
	int result=0;//char output
	while (1)
	{
		
		while (z=='T')
		{
			debounce();
			z=keypadscan();
			
		}
		lcd_clear();
		lcd_putchar(z);
		y=changetointger(z);
		_delay_ms(200);
		z='T';
		
		while (z=='T')
		{
			debounce();
			z=keypadscan();
		}
		lcd_putchar(z);
		o=z;
		_delay_ms(200);
		z='T';
		while (z=='T')
		{
			debounce();
			z=keypadscan();
		}
		lcd_putchar(z);
		r=changetointger(z);
		_delay_ms(200);
		z='T';
		while(z!='=')
		{
			debounce();
			z=keypadscan();
		}
		lcd_putchar(z);
		
		lcd_gotoxy(0,2);
		_delay_ms(200);
		if(o=='+')
		{
			result=y+r;
			
		}
		else if(o=='-')
		{
			result=y-r;
		}
		else if(o=='/'){
			result=y/r;
		}
		else if(o=='x'){
			result=y*r;
		}
		itoa (result,k,10);
		lcd_puts(k);
		z='T';
		result=0;
		r=0;
		y=0;
	}
}
/*#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "ALCD.H"



char str[]="";
//void SevenSegment(int x); //to inform compiler

int main(void)
{   
	lcd_init(16);
	int c = 0;
	int r = 0;
	int n = 0;
	int val = 0;
	int no1 = 0;
	int no2 = 0;
	int disp = 0;
	int calc = 0;
	DDRB = 0b00000000;
	DDRC = 0b00000000;
	PORTB = 0b00000000;
	PORTC = 0b00000000;
	PORTB|=(1<<0);
	PORTB|=(1<<1);
	PORTB|=(1<<2);
	PORTB|=(1<<3);
	PORTB|=(1<<4);
	PORTC|=(1<<0);
	PORTC|=(1<<1);
	PORTC|=(1<<2);
	PORTC|=(1<<3);
	PORTC|=(1<<4);
	//PINB |= BUTTON_MASK_up; // Enable internal PULLUP resistor on the input pin
	
	while (1)
	{
		//column
		DDRB = 0b00000001;
		if((PINB &(0b00000000)) == 0){
			lcd_clear();
			c = 1;
			n++;
		}
		DDRB = 0b00000010;
		if((PINB &(0b00000000)) == 0){
			lcd_clear();
			c = 2;
			n++;
		}
		DDRB = 0b00000100;
		if((PINB &(0b00000000)) == 0){
			lcd_clear();
			c = 3;
			n++;
		}
		DDRB = 0b00001000;
		if((PINB &(0b00000000)) == 0){
			lcd_clear();
			c = 4;
			n++;
		}
		//row
		DDRC = 0b00000001;
		if((PINC &(0b00000000)) == 0){
			lcd_clear();
			r = 1;
		}
		DDRC = 0b00000010;
		if((PINC &(0b00000000)) == 0){
			lcd_clear();
			r = 2;
		}
		DDRC = 0b00000100;
		if((PINC &(0b00000000)) == 0){
			lcd_clear();
			r = 3;
		}
		DDRC = 0b00001000;
		if((PINC &(0b00000000)) == 0){
			lcd_clear();
			r = 4;
		}
		//xjjmd
		if(n == 1){
		if(r == 1 && c == 1){
			no1 = 1;
		}
		if(r == 1 && c == 2){
			no1 = 2;
		}
		if(r == 1 && c == 3){
			no1 = 3;
		}
		if(r == 2 && c == 1){
			no1 = 4;
		}
		if(r == 2 && c == 1){
			no1 = 5;
		}
		if(r == 2 && c == 1){
			no1 = 6;
		}
		if(r == 3 && c == 1){
			no1 = 7;
		}
		if(r == 3 && c == 2){
			no1 = 8;
		}
		if(r == 3 && c == 3){
			no1 = 9;
		}
		if(r == 4 && c == 2){
			no1 = 0;
		}
		}
		if(n == 3){
			if(r == 1 && c == 1){
				no2 = 1;
				//n = 0;
			}
			if(r == 1 && c == 2){
				no2 = 2;
				//n = 0;
			}
			if(r == 1 && c == 3){
				no2 = 3;
				//n = 0;
			}
			if(r == 2 && c == 1){
				no2 = 4;
				//n = 0;
			}
			if(r == 2 && c == 1){
				no2 = 5;
				//n = 0;
			}
			if(r == 2 && c == 1){
				no2 = 6;
				//n = 0;
			}
			if(r == 3 && c == 1){
				no2 = 7;
				//n = 0;
			}
			if(r == 3 && c == 2){
				no2 = 8;
				//n = 0;
			}
			if(r == 3 && c == 3){
				no2 = 9;
				//n = 0;
			}
			if(r == 4 && c == 2){
				no2 = 0;
				//n = 0;
			}
		}
		if(n == 2){
			if(r == 1 && c == 4){
				calc = 1; //add
			}
			if(r == 3 && c == 4){
				calc = 2;//sub
			}
			if(r == 4 && c == 1){
				calc = 3;//multiplication
			}
			if(r == 4 && c == 3){
				disp = 1;//equal
			}
			if(r == 4 && c == 4){
				calc = 4;//division
			}
		}
		if(calc == 1 && n == 3){
			val = no1 + no2;
		}
		if(calc == 2 && n == 3){
			val = no1 - no2;
		}
		if(calc == 3 && n == 3){
			val = no1 * no2;
		}
		if(calc == 4 && n == 3){
			val = no1/no2;
		}
		if(n == 4){
			if(calc == 1){
				val = no1 + no2;
			}
			if(calc == 2){
				val = no1 - no2;
			}
			if(calc == 3){
				val = no1 * no2;
			}
			if(calc == 4){
				val = no1/no2;
			}
		}
		char snum[5];
		itoa(val, snum, 10);
		if(disp == 1 && n == 4){
			lcd_gotoxy(0,1);
			lcd_clear();
			lcd_puts(snum);
			disp = 0;
			n = 0;
		}
		lcd_gotoxy(0,0);
		lcd_puts(str); 
		_delay_ms(20);   
	}
	}
void SevenSegment(int x)
{   switch (count)
	{   case 0: PORT_7_SEGMENT=0b01011111; break;
		case 1: PORT_7_SEGMENT=0b00000110; break;
		case 2: PORT_7_SEGMENT=0b00111011; break;
		case 3: PORT_7_SEGMENT=0b00101111; break;
		case 4: PORT_7_SEGMENT=0b01100110; break;
		case 5: PORT_7_SEGMENT=0b01101101; break;
		case 6: PORT_7_SEGMENT=0b01111101; break;
		case 7: PORT_7_SEGMENT=0b00000111; break;
		case 8: PORT_7_SEGMENT=0b01111111; break;
		case 9: PORT_7_SEGMENT=0b01101111; break;
	}
}
*/