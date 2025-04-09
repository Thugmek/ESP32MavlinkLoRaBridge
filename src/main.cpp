#include "config.h"
#include "hal.hpp"
#include "buffer.hpp"
#include "mavlink_packet.hpp"
#include <string.h>

#ifdef MCU_ESP32
    #error "Tohle vole nechceš..."
    #include <Arduino.h>
#endif

#ifdef PLATFORM_LINUX
    #include <iostream>
    using namespace std;
#endif

void setup() {
    hal_debug("I'm setup");
}

void loop() {
    hal_debug("I'm loop");
    hal_delay(1000);
}

#ifdef PLATFORM_LINUX
int main(int argc, char *argv[]){

    cout << "LoRa server: " << (*argv[2]=='A') << "\n";
    select_LoRa_socket_role(*argv[2]=='A');
    LoRa_init();

    uint8_t receive_buff[255];
    uint8_t send_buff[] = "Hello world";

    while(1){
        cout << "Cycle start\n";
        if(LoRa_available()){
            cout << "LoRa available\n";
            LoRa_receive(receive_buff);
            cout << "Received: " << receive_buff << "\n";
        }
        cout << "LoRa send\n";
        LoRa_send(send_buff, 255);
        hal_delay(1000);
    }

    return 0;

    cout << "Serial port: " << argv[1] << "\n";
    select_serial_port(string(argv[1]));
    serial_init();

    while(1){
        if(serial_available()){
            cout.setf(ios::hex, ios::basefield);
            cout << (int)serial_read();
            cout.unsetf(ios::hex);
            cout << ", ";
        }else{
            hal_delay(1);
        }
    }

    return 0;
    
    //uint8_t data[] = {0xfd, 0x01, 0x00, 0x00, 0x3e, 0xff, 0xe6, 0x15, 0x00, 0x00, 0x00, 0x19, 0x92};
    //uint8_t data[] = {0xfd, 0x09, 0x00, 0x00, 0xa1, 0xff, 0xe6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x08, 0x00, 0x00, 0x03, 0x83, 0xb0};
    uint8_t data[] = {0xfd, 0x1e, 0x00, 0x00, 0xa0, 0xff, 0xe6, 0x4c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9a, 0x01, 0xa4, 0xea};

    Mavlink2Packet packet2(data,64);
    packet2.debug();

    return 0;

    setup();
    while(1){
        loop();
    }
    return 0;
}
#endif
