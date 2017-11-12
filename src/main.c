#include <avr/io.h>

#include "modules/sensor.h"
#include "modules/buzzer.h"

#include "init.h"
#include "connector.h"
#include "scheduler.h"

int main()
{
    // Initialization
    init_adc();
    init_uart();
    init_timer();
    init_ports();

    scheduler_init_t1();

    // Needs to be multiplied. Currently used for testing
    int time = SENSOR_MODE == 0 ? 300 : 400;

    //scheduler_add_task(run_sensor_scan, time, time);
    //scheduler_add_task(report_average, 600, 600);
    scheduler_add_task(check_for_messages, 0, 100);

    scheduler_start();

    PORTB = 0x00;

    while (1)
    {
        scheduler_dispatch_tasks();
    }
}