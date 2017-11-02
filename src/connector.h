#ifndef dev_connector_h
#define dev_connector_h

#define UBBRVAL 51
#define BAUD 19200

#define SET_SETTING 0b00010000
#define ROLL_UP     0b00100000
#define ROLL_DOWN   0b00110000
#define REPORT      0b01000000
#define END_TRANSM  0b01110000

void transmit(uint8_t data);
uint8_t receive();
void check_for_messages();
void init_connector();

float create_float(uint8_t integer);

#endif