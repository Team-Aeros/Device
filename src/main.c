#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "modules.h"
#include "status.h"
#include "init.h"
#include "control.h"

int main()
{
	port_init();
	adc_init();
	
	while(1)
	{
		lightSensor();
	}
}