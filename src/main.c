#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "modules.h"
#include "status.h"
#include "init.h"
#include "control.h"
#include "scheduler.h"

int main()
{
    init_connector();
    port_init();
    adc_init();

    sch_init_t1();
    sch_start();

    sch_add_task(run_temperature_scan, 0, 40);
    sch_add_task(report_average_temperature, 0, 60);

    while (1)
    {
        sch_dispatch_tasks();
    }

    return 0;
}