#define F_CPU 16000000UL

#include "shutter.h"

#include <avr/io.h>
#include <util/delay.h>

#include "buzzer.h"
#include "distance_sensor.h"

#include "../settings.h"

/**
 * Rolls the shutter up or down
 * @param distance The distance
 * @param direction The direction (UP or DOWN)
 */
void roll_shutter(float distance, int direction)
{
    //float roll_time = distance / 0.05;
    
    PORTB &= ~_BV(direction == DOWN ? PB5 : PB4);
    PORTB |= _BV(direction == DOWN ? PB4 : PB5);
    
    // Uncomment when distance sensor is working
    if (direction == DOWN)
    {
        while (read_distance() < (distance * 100))
        {
            PORTB |= _BV(PB3);
            buzz(300);
            _delay_ms(500);
            PORTB &= ~_BV(PB3);
            buzz(250);
            _delay_ms(500);
        }
        
        stop_buzz();
    }
    else
    {
        while (read_distance() > 5)
        {
            PORTB |= _BV(PB3);
            buzz(300);
            _delay_ms(500);
            PORTB &= ~_BV(PB3);
            buzz(250);
            _delay_ms(500);
        }
    
        stop_buzz();
    }
}