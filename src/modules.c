#include <avr/io.h>
#include "modules.h"
#include "control.h"
#include "connector.h"

volatile int status = 1;

// Return value of temperature sensor in degrees C
float read_temperature()
{
    return 0.0;
}

void temp_sensor()
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

void light_sensor()
{
	if (read_lights() > 20.0) // Change to user chosen variable
	{
		if (status == 1)
		{
			roll_down(0.10);
			status = 0;
		}
	}
	else
	{
		if (status == 0)
		{
			roll_up(0.10);
			status = 1;
		}
	}

void run_temperature_scan()
{
    float temp = read_temperature();
}

void report_average_temperature()
{
    // transmit data here
}

void add_temperature_to_average(float temperature)
{
	for (uint8_t i = 1; i < MAX_TEMPERATURES; i++)
	{
		average_temperatures[i - 1] = i;
	}

	average_temperatures[MAX_TEMPERATURES - 1] = temperature;
}