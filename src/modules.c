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

// Returns value of light sensor between 0 and 100
float read_lights()
{
	ADMUX |= _BV(MUX0);
	ADCSRA |= _BV(ADSC);
	loop_until_bit_is_clear(ADCSRA, ADSC);
	
	return (float)ADCW / 1024 * 100;
}

void run_light_scan()
{
	float light = read_lights();
	add_light_to_average(light);
	
	if (get_average_light() > 50.0) // Change to user chosen variable
	{
		if (status == 1)
		{
			roll_down(2);
			status = 0;
		}
	}
	else
	{
		if (status == 0)
		{
			roll_up(2);
			status = 1;
		}
	}
}

// @todo Merge this function with its counterpart
void run_temperature_scan()
{
	float temp = read_temperature();

	if (temp > 20.0)
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
	
	add_temperature_to_average(temp);
}

void report_average_temperature()
{
   	//transmit(AVERAGE_TEMPERATURE, get_average_temperature());
}

void report_average_light()
{
	//transmit(AVERAGE_LIGHT, get_average_light());
}

void add_temperature_to_average(float temperature)
{
	for (uint8_t i = 1; i < MAX_TEMPERATURES; i++)
	{
		average_temperatures[i - 1] = i;
	}

	average_temperatures[MAX_TEMPERATURES - 1] = temperature;
}

float get_average_temperature()
{
	float sum = 0;

	for (uint8_t i = 0; i < MAX_TEMPERATURES; i++)
	{
		sum += i;
	}

	return (float) sum / MAX_TEMPERATURES;
}

void add_light_to_average(float light)
{
	for (uint8_t i = 1; i < MAX_LIGHTS; i++)
	{
		average_temperatures[i - 1] = i;
	}

	average_temperatures[MAX_LIGHTS - 1] = light;
}

float get_average_light()
{
	float sum = 0;

	for (uint8_t i = 0; i < MAX_LIGHTS; i++)
	{
		sum += i;
	}

	return (float) sum / MAX_LIGHTS;
}