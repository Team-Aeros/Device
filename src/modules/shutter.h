#ifndef dev_shutter_h
#define dev_shutter_h

typedef enum Direction {
    UP,
    DOWN
} Direction;

void roll_shutter(float distance, int direction);

#endif