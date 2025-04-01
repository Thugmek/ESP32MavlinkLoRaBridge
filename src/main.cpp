#include "config.h"
#include "hal.hpp"

/*#ifdef MCU_ESP32
    #error "Tohle vole nechceš..."
    #include <Arduino.h>
#endif*/

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
    cout << argv[1] << "\n";
    setup();
    serial_init();
    while(1){
        loop();
    }
    return 0;
}
#endif
