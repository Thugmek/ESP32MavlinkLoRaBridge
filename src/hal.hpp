#include <cstdint>
#include <string>

void hal_delay(uint16_t ms);
void hal_debug(std::string msg);

#ifdef PLATFORM_LINUX
void select_LoRa_socket_role(bool server);
#endif
void LoRa_init();
void LoRa_send_message(uint8_t *data, uint8_t len);

#ifdef PLATFORM_LINUX
void select_serial_port(std::string port);
#endif
void serial_init();
void serial_write(std::string msg);
uint8_t serial_read();
bool serial_available();