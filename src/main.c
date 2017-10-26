#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "status.h"
#include "init.h"
#include "modules/sensor.h"
#include "connector.h"
#include "scheduler.h"

int main()
{
    init_connector();
    port_init();
    adc_init();

    sch_init_t1();
    sch_start();
    
	if (SENSOR_MODE == 0) // Light sensor
	{
		sch_add_task(run_sensor_scan, 3000, 3000);
	}
	else if (SENSOR_MODE == 1) // Temp sensor
	{
		sch_add_task(run_sensor_scan, 4000, 4000);
	}
	

    sch_add_task(report_average, 0, 6000);

    while (1)
    {
        sch_dispatch_tasks();
    }

    return 0;
}