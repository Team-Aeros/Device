#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "init.h"
#include "modules/sensor.h"
#include "connector.h"
#include "scheduler.h"
#include "settings.h"

int main()
{
    init_connector();
    port_init();
    adc_init();

    sch_init_t1();
    sch_start();
    
	int time = SENSOR_MODE == 0 ? 3000 : 4000; sch_add_task(run_sensor_scan, time, time);

    sch_add_task(report_average, 0, 6000);
    sch_add_task(check_for_messages, 0, 200);

    while (1)
    {
        sch_dispatch_tasks();
    }

    return 0;
}