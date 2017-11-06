#include <avr/io.h>
#include "sensor.h"
#include "control.h"
#include "../connector.h"
#include "../settings.h"
#include "light_sensor.h"
#include "temp_sensor.h"

// 0 = down, 1 = up
volatile int status = 1;

float read_sensor()
{
    return SENSOR_MODE == 0 ? read_light() : read_temp();
}

void run_sensor_scan()
{
	float reading = read_sensor();
	add_to_average(reading);
	
	if (read_sensor() > roll_down_value) // Change to user chosen variable
	{
		if (status == 1)
		{
			//roll_shutter(length, DOWN);
			status = 0;
			transmit(0b11111111);
			transmit(0b01010000);
			transmit(0b01110000);
		}
	}
	else
	{
		if (status == 0)
		{
			//roll_shutter(length, UP);
			status = 1;
			transmit(0b11111111);
			transmit(0b01010001);
			transmit(0b01110000);
		}
	}
}

void report_average()
{	
	float average = get_average() * 10;
	int result;

    transmit(0b11111111);
    transmit(0b01000000);
 
	while (average > 0)
	{
		if ((result = average - 255) > 0)
		{
			transmit(255);
			average -= 255;
		}
		else
		{
			transmit(average);
			break;
		}
	}

    transmit(0b01110000);
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