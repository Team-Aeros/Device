/* This file is based on code provided by the Hanze university */
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stdlib.h>
#include <stdio.h>
#include "connector.h"
#include "modules/control.h"

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
}

uint8_t receive()
{
    //loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;
}

void check_for_messages()
{
    uint8_t message;
    uint8_t type;
    uint8_t continued = 0;

    if (receive() != 0xFF)
    {
        return;
    }

    while (1)
    {
        message = receive();

        if (message == 0x00)
        {
            return;
        }

        if (continued == 0)
        {
            type = message & 0xF0;
            switch (type)
            {
                case SET_SETTING:
                    printf("hi");
                case ROLL_UP:
                    roll_up();
                    return;
                case ROLL_DOWN:
                    roll_down();
                    return;
                case REPORT:
                case END_TRNSM:
                    break;
            }
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