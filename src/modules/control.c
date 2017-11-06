#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "control.h"

// Roll up or down
void roll_shutter(float distance, int direction)
{
    float roll_time = distance / 0.05;
    
    PORTD &= ~_BV(direction == DOWN ? PD7 : PD6);
    PORTD |= _BV(direction == DOWN ? PD6 : PD7);
    
    for (int i = 0; i < roll_time; i ++)
    {
        PORTD |= _BV(PD5);
        _delay_ms(500);
        PORTD &= ~_BV(PD5);
        _delay_ms(500);
    }
}