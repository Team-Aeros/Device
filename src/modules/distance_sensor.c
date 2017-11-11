#define F_CPU 16000000UL

#include "distance_sensor.h"

#include <avr/io.h>
#include <util/delay.h>

#include "../connector.h"

float read_distance()
{
	PORTD |= _BV(PD3);
	_delay_us(20);
	PORTD &= ~_BV(PD3);

	loop_until_bit_is_set(PIND, PD4);
	TCNT1 = 0;
	PORTB |= _BV(PB3);
	loop_until_bit_is_clear(PIND, PD4);
	PORTB &= ~_BV(PB3);
	unsigned int count = TCNT1;
	//transmit(TCNT1);
	float distance = ((float)count / 16) / 58;

	return distance;
}