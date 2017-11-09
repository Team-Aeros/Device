#include "settings.h"

#include <avr/io.h>
#include <util/delay.h>

#include "init.h"
#include "modules/sensor.h"
#include "connector.h"
#include "scheduler.h"

int main()
{
    init_connector();
    init_ports();
    init_analog();

    scheduler_init_t1();

    int time = SENSOR_MODE == 0 ? 300 : 400;

    //scheduler_add_task(run_sensor_scan, time, time);
    //scheduler_add_task(report_average, 600, 600);
    //scheduler_add_task(check_for_messages, 0, 100);

    scheduler_start();

    PORTD = 0x00;

    while (1)
    {
        int reading = (int) read_sensor();

        transmit(0xFF);
        transmit(0b01000000);
        transmit(reading);
        transmit(0b01110000);

        if (reading > 200)
        {
            PORTD |= _BV(PD7);
        }
        else if (reading > 100)
        {
            PORTD |= _BV(PD5);
        }
        else if (reading > 20)
        {
            PORTD |= _BV(PD6);
        }
        else
        {
            PORTD = 0xFF;
        }

        _delay_ms(300);
        //scheduler_dispatch_tasks();
    }

    return 0;
}