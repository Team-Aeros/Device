#include <avr/io.h>
#include "sensor.h"
#include "../control.h"
#include "../connector.h"
#include "light_sensor.h"
#include "temp_sensor.h"

volatile int status = 1;

float read_sensor()
{
	if (SENSOR_MODE == 0)
	{
		return read_light();
	}
	else if (SENSOR_MODE == 1)
	{
		return read_temp();
	}
}

void run_sensor_scan()
{
	float reading = read_sensor();
	add_to_average(reading);
	
	if (get_average() > 50.0) // Change to user chosen variable
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

void report_average()
{
	//transmit(AVERAGE_LIGHT, get_average_light());
}

void add_to_average(float value)
{
	for (uint8_t i = 1; i < MAX_VALUES; i++)
	{
		average[i - 1] = average[i];
	}

	average[MAX_VALUES - 1] = value;
}

float get_average()
{
	float sum = 0;

	for (uint8_t i = 0; i < MAX_VALUES; i++)
	{
		sum += average[i];
	}

	return (float) sum / MAX_VALUES;
}