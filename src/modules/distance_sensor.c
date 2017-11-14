#define F_CPU 16000000UL

#include "distance_sensor.h"

#include <avr/io.h>
#include <util/delay.h>

/**
 * Used for reading data from the distance sensor.
 * @return The distance sensor reading
 */
float read_distance()
{
	PORTD |= _BV(PD3);
	_delay_us(10);
	PORTD &= ~_BV(PD3);

	loop_until_bit_is_set(PIND, PD4);
	TCNT1 = 0;
	loop_until_bit_is_clear(PIND, PD4);
	uint16_t count = TCNT1;

	return ((float) count / 4);
}