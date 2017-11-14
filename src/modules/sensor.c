#define F_CPU 16000000UL

#include "sensor.h"

#include <avr/io.h>
#include <util/delay.h>
#include <math.h>

#include "light_sensor.h"
#include "temp_sensor.h"
#include "shutter.h"

#include "../connector.h"
#include "../settings.h"

// Begin status of shutter. 0 = rolled down, 1 = rolled up
volatile int status = 1;

/**
 * Returns the reading from the appropriate sensor.
 * @return Said reading
 */
float read_sensor()
{
    return SENSOR_MODE == 0 ? read_light() : read_temp();
}

/**
 * Runs a scan of the correct sensor
 */
void run_sensor_scan()
{
    add_to_average(read_sensor());

    if (!in_manual_mode)
    {
        toggle_status();        
    }
}

/**
 * Rolls the shutter up or down based on the average sensor value
 */
void toggle_status()
{
    if (get_average() > roll_down_value)
    {
        if (status == 1)
        {
            roll_shutter(length, DOWN);
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
            roll_shutter(length, UP);
            status = 1;
            
            transmit(0b11111111);
            transmit(0b01010001);
            transmit(0b01110000);
        }
    }
}

/**
 * Transmits the average sensor reading to the GUI.
 */
void report_average()
{   
    float average = round(get_average() * 10);
    int result;

    transmit(0b11111111);
    transmit(0b01000000);
 
    while (average > 0)
    {
        // This can be edited if we ever decide to bring back the confirmation messages
        int is_instruction = average == 0b01110000;

        if ((average - 255) > 0 && !is_instruction)
        {
            transmit(0b11111111);
            average -= 255;
        }
        else if (is_instruction)
        {
            transmit(average / 2);
            transmit(average / 2);
            break;
        }
        else
        {
            transmit(average);
            break;
        }
    }

    transmit(0b01110000);
}

/**
 * Adds a value to the average array and removes the first value.
 */
void add_to_average(float value)
{
    for (uint8_t i = 1; i < MAX_VALUES; i++)
    {
        average[i - 1] = average[i];
    }

    average[MAX_VALUES - 1] = value;
}

/**
 * Calculates the average while taking the exact number of values into account.
 * @returns The average
 */
float get_average()
{
    float sum = 0;
    uint8_t actual_value_count = 0;
    uint8_t value;

    for (uint8_t i = 0; i < MAX_VALUES; i++)
    {
        value = average[i];
        sum += value;

        if (value > 0)
        {
            actual_value_count++;
        }
    }

    return (float) sum / actual_value_count;
}