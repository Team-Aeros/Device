/* This file is based on code provided by the Hanze university */
#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

#include "connector.h"
#include "modules/control.h"
#include "settings.h"

typedef enum DataType
{
    LIGHT_SENSOR,
    TEMPERATURE_SENSOR,
    AVERAGE_TEMPERATURE
} DataType;

void transmit(uint8_t data)
{
    do
    {
        loop_until_bit_is_set(UCSR0A, UDRE0);
        UDR0 = data;
    } while (receive() != CONFIRM);
}

uint8_t receive()
{
    loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;
}

void check_for_messages()
{
    return;
    uint8_t message;
    uint8_t type;
    uint8_t args;
    uint8_t value = 0;

    // Has a connection been established?
    if (receive() != 0xFF)
    {
        PORTD |= _BV(PD7);
        return;
    }

    transmit(0b01100000)
;
    PORTD |= _BV(PD6);

    while (1)
    {
        message = receive();

        if (message == 0x00)
        {
            return;
        }

        // Send confirmation message
        transmit(0b01100000);

        type = message & 0xF0;
        args = message & 0x0F;

        switch (type)
        {
            case SET_SETTING:
                while (1)
                {
                    message = receive();

                    if (message == 0b0111000)
                    {
                        value /= 10;

                        // set setting
                        switch (args)
                        {
                            case SETTING_LENGTH:
                                // length = value
                            case SETTING_ROLL_DOWN_VALUE:
                                // roll_down_value = value
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

        _delay_ms(10);
    }
}

void init_connector()
{
    UBRR0H = 0;
    UBRR0L = UBBRVAL;

    UCSR0A = 0;
    UCSR0B = _BV(TXEN0) | _BV(RXEN0);
    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
}

float create_float(uint8_t integer)
{
    return (float) integer / 10;
}