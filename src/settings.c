#include "settings.h"
#include "modules/sensor.h"

/**
 * The roll out length
 */
float length = 0.40;

/**
 * Equivalent of min_val in the GUI.
 */
float roll_down_value = SENSOR_MODE == 0 ? 50 : 22;

/**
 * If we're in manual mode, this should be set to 1. If not
 * this should, surprisingly, be set to 0.
 */
int in_manual_mode = 0;