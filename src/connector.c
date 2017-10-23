/**
 * This file is based on code provided by the Hanze university
 */

#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stdlib.h>
#include "connector.h"

#define UBBRVAL 51

typedef enum DataType
{
    LIGHT_SENSOR,
    TEMPERATURE_SENSOR,
    AVERAGE_TEMPERATURE
} DataType;

void transit(uint8_t type, uint8_t data)
{
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = type + data;
}

uint8_t receive()
{
    loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;
}

void init_connector()
{
    UBRR0H = 0;
    UBRR0L = UBBRVAL;

    UCSR0A = 0;
    UCSR0B = _BV(TXEN0) | _BV(RXEN0);
    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
}