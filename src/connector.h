#ifndef dev_connector_h
#define dev_connector_h

#define UBBRVAL 51
#define BAUD 19200

void transmit(uint8_t type, uint8_t data);
uint16_t receive();
void check_for_messages();
void init_connector();

#endif