#include <avr/io.h>
#include <avr/sfr_defs.h>
#include "init.h"

void init_analog()
{
	ADCSRA |= _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
	ADMUX |= _BV(REFS0);
	ADMUX &= ~_BV(REFS1);
	ADCSRA |= _BV(ADEN);
}

void init_ports()
{
	DDRD = 0xff;
	PORTD |= _BV(PD7);
}

void init_connector()
{
    UBRR0H = 0;
    UBRR0L = UBBRVAL;

    UCSR0A = 0;
    UCSR0B = _BV(TXEN0) | _BV(RXEN0);
    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
}