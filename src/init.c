#include "init.h"

#include <avr/io.h>

void init_adc()
{
	ADCSRA |= _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
	ADMUX |= _BV(REFS0);
	ADMUX &= ~_BV(REFS1);
	ADCSRA |= _BV(ADEN);
}

void init_ports()
{
	// LEDs
	DDRB |= _BV(PB5); // Red LED
	DDRB |= _BV(PB4); // Green LED
	DDRB |= _BV(PB3); // Yellow LED

	PORTB |= _BV(PB5); // Turn red LED on by default

	// Buzzer
	DDRD |= _BV(PD6);

	// Distance sensor
	DDRD |= _BV(PD3); // Trigger
	DDRD &= ~_BV(PD4); // Echo

	// Light/Temp sensor
	DDRC &= ~_BV(PC1); // Input sensor
}

void init_uart()
{
    UBRR0H = 0;
    UBRR0L = UBBRVAL;

    UCSR0A = 0;
    UCSR0B = _BV(TXEN0) | _BV(RXEN0);
    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
}

void init_timer()
{
	// Used for distance sensor
	TCCR1B |= _BV(CS10);
	//TCCR1A |= _BV(CS10);
}
