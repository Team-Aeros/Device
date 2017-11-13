#include "settings.h"
#include "modules/sensor.h"

float length = 0.40;
float roll_down_value = SENSOR_MODE == 0 ? 50 : 22;

int in_manual_mode = 0;