#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "modules.h"
#include "status.h"
#include "init.h"
#include "control.h"
#include "connector.h"
#include "scheduler.h"

typedef enum Mode
{
    LIGHT_SENSOR,
    TEMPERATURE_SENSOR
} Mode;

const uint8_t SENSOR_MODE = TEMPERATURE_SENSOR;

int main()
{
    init_connector();
    port_init();
    adc_init();

    sch_init_t1();
    sch_start();

    if (SENSOR_MODE == TEMPERATURE_SENSOR)
    {
        sch_add_task(run_temperature_scan, 4000, 4000);
    }
    else
    {
        sch_add_task(run_light_scan, 3000, 3000);
    }

    sch_add_task(SENSOR_MODE == TEMPERATURE_SENSOR ? report_average_temperature : report_average_temperature, 0, 6000);

    while (1)
    {
        sch_dispatch_tasks();
    }

    return 0;
}