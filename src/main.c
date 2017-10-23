#include <avr/io.h>
#include "connector.h"
#include "modules.h"
#include "status.h"
#include "scheduler.h"

// 0 = light sensor, 1 = temperature sensor
const uint8_t MODE = 1;

int main()
{
    DDRD = 0xFF;
    PORTD = 0xFF;

    init_connector();

    sch_init_t1();
    sch_start();

    sch_add_task(MODE == 0 ? run_temperature_scan : run_temperature_scan, 0, 40);
    sch_add_task(MODE == 0 ? report_average_temperature : report_average_temperature, 0, 60);

    while (1)
    {
        sch_dispatch_tasks();
    }

    return 0;
}