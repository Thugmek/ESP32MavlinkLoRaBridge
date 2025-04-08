#include <cstdint>
#include <string>

void hal_delay(uint16_t ms);
void hal_debug(std::string msg);

#ifdef PLATFORM_LINUX
void select_LoRa_socket_role(bool server);
#endif
void LoRa_init();
void LoRa_send(uint8_t *data, uint16_t len);
uint16_t LoRa_receive(uint8_t *data);
bool LoRa_available();

#ifdef PLATFORM_LINUX
void select_serial_port(std::string port);
#endif
void serial_init();
void serial_write(std::string msg);
uint8_t serial_read();
bool serial_available();