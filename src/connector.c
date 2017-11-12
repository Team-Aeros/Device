/* This file is based on code provided by the Hanze university */
#include "settings.h"

#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "connector.h"
#include "modules/shutter.h"

typedef enum DataType
{
    LIGHT_SENSOR,
    TEMPERATURE_SENSOR,
    AVERAGE_TEMPERATURE
} DataType;

void transmit(uint8_t data)
{
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = data;
    //_delay_ms(10);
}

uint8_t receive()
{
    for (uint8_t i = 0; i < 20; i++)
    {
       	if (!bit_is_clear(UCSR0A, RXC0))
       	{
        	return UDR0;
       	}
		_delay_ms(2);
    }

    return 0;
}

/*uint8_t receive()
{
	loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;
}*/

void check_for_messages()
{
    uint8_t message;
    uint8_t type;
    uint8_t args;
    float value = 0;

    // Has a connection been established?
    if (receive() != 0xFF)
    {
        //PORTD |= _BV(PD7);
        return;
    }

    // Confirm we've established a connection
    //transmit(0b01100000);

    while (1)
    {
        message = receive();

        if (message == 0x00)
        {
            return;
        }

        // Send confirmation message
        //transmit(0b01100000);

        type = message & 0xF0;
        args = message & 0x0F;

        switch (type)
        {
            case SET_SETTING:
                if (args == SETTING_IN_MANUAL_MODE)
                {
                    in_manual_mode = in_manual_mode ? 0 : 1;
                    return;
                }

                while (1)
                {
                    message = receive();

                    if (message == 0b01110000)
                    {
                        value /= 10;

                        switch (args)
                        {
                            case SETTING_LENGTH:
                                length = value;
                                PORTB |= _BV(PB3);
                                break;
                            case SETTING_ROLL_DOWN_VALUE:
                                roll_down_value = value;
                                //PORTB |= _BV(PB3);
                                break;
                            default:
                                transmit(0b01011111);
                                value = 0;
                                return;
                        }

                        value = 0;
                        return;
                    }

                    value += message;
                }
                break;
            case ROLL_UP:
                roll_shutter(length, UP);
                return;
            case ROLL_DOWN:
                roll_shutter(length, DOWN);
                return;
            case REPORT:
            case END_TRANSM:
                return;
        }

        //_delay_ms(10);
    }
}

float create_float(uint8_t integer)
{
    return (float) integer / 10;
}