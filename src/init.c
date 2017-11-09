#include <avr/io.h>
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