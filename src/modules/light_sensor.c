#include <avr/io.h>
#include "light_sensor.h"

// Returns value of light sensor between 0 and 100
float read_light()
{
	ADMUX |= _BV(MUX0);
	ADCSRA |= _BV(ADSC);
	loop_until_bit_is_clear(ADCSRA, ADSC);
	
	return (float)ADCW / 1024 * 100;
}