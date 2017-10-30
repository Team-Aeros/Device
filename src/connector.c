/* This file is based on code provided by the Hanze university */
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stdlib.h>
#include <stdio.h>
#include "connector.h"

typedef enum DataType
{
    LIGHT_SENSOR,
    TEMPERATURE_SENSOR,
    AVERAGE_TEMPERATURE
} DataType;

void transmit(uint8_t type, uint8_t data)
{
    loop_until_bit_is_set(UCSR0A, UDRE0);

    // Sorry. I know.
    char str[8];
    sprintf(str, "%d%d", type, data);
    UDR0 = (uint16_t) atoi(str);
}

uint16_t receive()
{
    //loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;
}

void check_for_messages()
{
    uint16_t message = receive();
    
    uint16_t type = message;
}

void init_connector()
{
    UBRR0H = 0;
    UBRR0L = UBBRVAL;

    UCSR0A = 0;
    UCSR0B = _BV(TXEN0) | _BV(RXEN0);
    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
}