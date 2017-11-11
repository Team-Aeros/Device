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

    // @todo: x10
    int time = SENSOR_MODE == 0 ? 300 : 400;

    //scheduler_add_task(run_sensor_scan, time, time);
    //scheduler_add_task(report_average, 600, 600);
    //scheduler_add_task(check_for_messages, 0, 100);

    //scheduler_start();

    PORTD = 0x00;
    const int TEST_VALUE = 20;

    while (1)
    {
        if (read_sensor() > TEST_VALUE)
        {
            PORTD = 0xFF;
        }

        //scheduler_dispatch_tasks();
    }

    return 0;
}