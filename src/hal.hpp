#include <cstdint>
#include <string>

void hal_delay(uint16_t ms);
void hal_debug(std::string msg);

void LoRa_init();
void LoRa_send_message(uint8_t *data, uint8_t len);

void serial_init();
void serial_write(std::string msg);
void serial_read();