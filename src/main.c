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
    scheduler_start();

    int time = SENSOR_MODE == 0 ? 300 : 4000;

    scheduler_add_task(run_sensor_scan, time, time);
    scheduler_add_task(report_average, 600, 600);
    scheduler_add_task(check_for_messages, 0, 100);

    while (1)
    {
        scheduler_dispatch_tasks();
    }

    return 0;
}