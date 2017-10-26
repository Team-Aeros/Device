#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "control.h"

// Rolldown to user set variable
void roll_down(float distance)
{
	float roll_time = distance / 0.05;
	
	PORTD &= ~_BV(PD7);
	PORTD |= _BV(PD6);
	
	for (int i = 0; i < roll_time; i ++)
	{
		PORTD |= _BV(PD5);
		_delay_ms(500);
		PORTD &= ~_BV(PD5);
		_delay_ms(500);
	}
}

// Rollup to user set variable
void roll_up(float distance)
{
	float roll_time = distance / 0.05;
	
	PORTD &= ~_BV(PD6);
	PORTD |= _BV(PD7);
	
	for (int i = 0; i < roll_time; i ++)
	{
		PORTD |= _BV(PD5);
		_delay_ms(500);
		PORTD &= ~_BV(PD5);
		_delay_ms(500);
	}
}