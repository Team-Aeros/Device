#include <avr/io.h>
#include "temp_sensor.h"

/**
 * Gets the temperature sensor reading.
 * @return The current temperature in degrees C
 */
float read_temp()
{
	ADMUX &= ~_BV(MUX0);
	ADCSRA |= _BV(ADSC);
	loop_until_bit_is_clear(ADCSRA, ADSC);
	
	return (float) ((ADCW * 5000 / 1024) - 500) / 10;
}