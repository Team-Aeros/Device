#include "settings.h"
#include "modules/sensor.h"

float length = 1.50;
float roll_down_value = SENSOR_MODE == 0 ? 50 : 22;

int in_manual_mode = 0;