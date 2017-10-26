#ifndef dev_modules_h
#define dev_modules_h

#define MAX_TEMPERATURES 5
#define ROLL_SPEED 0.10

float read_temperature();
float read_lights();

void run_light_scan();
void run_temperature_scan();
void report_average_temperature();
void add_temperature_to_average(float temperature);

float get_average_temperature();

float average_temperatures[5];

#endif