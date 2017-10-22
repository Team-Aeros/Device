#include <avr/io.h>
#include "modules.h"

// Return value of temperature sensor in degrees C
void read_temperature()
{

}

// Returns value of light sensor between 0 and 100
float read_lights()
{
	ADMUX = _BV(MUX0);
	ADCSRA = _BV(ADSC);
	loop_until_bit_is_clear(ADCSRA, ADSC);

	return (float) ADCW / 1024 * 100;
}
