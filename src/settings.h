#ifndef dev_settings_h
#define dev_settings_h

#define F_CPU 16000000UL

extern float length;
extern float roll_down_value;

// Note: a regular int because uint8_t requires a certain .h file
extern int in_manual_mode;

#endif