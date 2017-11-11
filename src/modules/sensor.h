#ifndef dev_sensor_h
#define dev_sensor_h

#define MAX_VALUES 5
#define SENSOR_MODE 0 // 0 = light_sensor, 1 = temp_sensor 

float read_sensor();

void toggle_status();
void run_sensor_scan();
void report_average();
void add_to_average(float value);

float get_average();

float average[5];

#endif