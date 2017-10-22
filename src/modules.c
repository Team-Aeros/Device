#include <avr/io.h>
#include "modules.h"

// Return value of temperature sensor in degrees C
float read_temperature()
{

}

void tempSensor()
{
	
}

// Returns value of light sensor between 0 and 100
float read_lights()
{
	ADMUX |= _BV(MUX0);
	ADCSRA |= _BV(ADSC);
	loop_until_bit_is_clear(ADCSRA, ADSC);
	
	return (float)ADCW / 1024 * 100;
}

void lightSensor()
{
	if (read_lights() > 20.0)
	{
		PORTD = 0xff;
	}
	else
	{
		PORTD = 0x00;
	}
}