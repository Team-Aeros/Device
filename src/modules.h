#ifndef dev_modules_h
#define dev_modules_h

#define MAX_TEMPERATURES 5

float read_temperature();
float read_lights();

void run_temperature_scan();
void report_average_temperature();
void add_temperature_to_average(float temperature);

float average_temperatures[5];

#endif