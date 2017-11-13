#define F_CPU 16000000UL

#include "distance_sensor.h"

#include <avr/io.h>
#include <util/delay.h>

#include "../connector.h"

float read_distance()
{
	PORTD |= _BV(PD3);
	_delay_us(10);
	PORTD &= ~_BV(PD3);

	loop_until_bit_is_set(PIND, PD4);
	TCNT1 = 0;
	//PORTB |= _BV(PB3);
	loop_until_bit_is_clear(PIND, PD4);
	//PORTB &= ~_BV(PB3);
	uint16_t count = TCNT1;
	//transmit(count);
	float distance = ((float)count / 4);

	return distance;
}