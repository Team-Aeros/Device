#ifndef dev_modules_h
#define dev_modules_h

#define MAX_TEMPERATURES 5
#define MAX_LIGHTS 5

float read_temperature();
float read_lights();

void run_light_scan();
void run_temperature_scan();
void report_average_temperature();
void report_average_light();
void add_temperature_to_average(float temperature);
void add_light_to_average(float light);

float get_average_temperature();
float get_average_light();

float average_temperatures[5];

#endif