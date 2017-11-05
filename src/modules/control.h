#ifndef dev_control_h
#define dev_control_h

typedef enum Direction {
    UP,
    DOWN
} Direction;

void roll_shutter(float distance, int direction);

#endif