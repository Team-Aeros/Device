/* This file contains code written by teachers from the Hanze university */

#include "init.h"

#include <avr/io.h>

/**
 * Initializes everything we need for analog data reading. How about you leave this be?
 */
void init_adc()
{
	ADCSRA |= _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
	ADMUX |= _BV(REFS0);
	ADMUX &= ~_BV(REFS1);
	ADCSRA |= _BV(ADEN);
}

/**
 * Initializes the ports. We also need this, so please don't screw this up either.
 */
void init_ports()
{
    /**
     * LEDs and buzzers
     */

    // Red LED
	DDRB |= _BV(PB5);

    // Green LED
	DDRB |= _BV(PB4);

    // Yellow LED
	DDRB |= _BV(PB3);

    // The red LED should be turned on by default (because it looks cool)
	PORTB |= _BV(PB5);

	// Buzzer
	DDRD |= _BV(PD6);

	/*
     * Distance sensor
     */
    // Trigger(ed)
	DDRD |= _BV(PD3);

    // Echo
	DDRD &= ~_BV(PD4);

	/*
     * Light and temperature sensors
     */
	DDRC &= ~_BV(PC1);
}

/**
 * Initialize the UART system. Credits to Hanze for writing this code.
 */
void init_uart()
{
    UBRR0H = 0;
    UBRR0L = UBBRVAL;

    UCSR0A = 0;
    UCSR0B = _BV(TXEN0) | _BV(RXEN0);
    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
}

/**
 * We need a timer for the distance sensor. This function takes care of that.
 */
void init_timer()
{
	// Used for distance sensor
	TCCR1B |= _BV(CS10);
}
