#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "modules.h"
#include "status.h"
#include "init.h"
#include "control.h"
#include "scheduler.h"

// 0 = light sensor, 1 = temperature sensor
const uint8_t MODE = 1;

int main()
{
    init_connector();
    port_init();
    adc_init();

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