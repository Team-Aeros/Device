#include <avr/io.h>
#include "modules.h"
#include "control.h"

volatile int status = 1;

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
	if (read_lights() > 20.0) // Change to user chosen variable
	{
		if (status == 1)
		{
			rollDown(0.10);
			status = 0;
		}
	}
	else
	{
		if (status == 0)
		{
			rollUp(0.10);
			status = 1;
		}
	}
}