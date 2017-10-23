#ifndef dev_connector_h
#define dev_connector_h

void transmit(uint8_t type, uint8_t data);
uint8_t receive();
void init_connector();

#endif