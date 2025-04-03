#include <cstdint>
#include <stdio.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>
#include <fcntl.h> 
#include <errno.h>
#include <termios.h>
#include <string.h>

#include "../../config.h"
#include "../../buffer.hpp"

using namespace std;

void hal_delay(uint16_t ms){
    usleep(ms*1000);
}

void hal_debug(std::string msg){
    cout << msg << "\n";
}

CircularBuffer<uint8_t> serial_buffer(128);
string serial_port_name;
int serial_port;
void select_serial_port(string port)
{
    serial_port_name = port;
}

void serial_thread()
{
    cout << "Thread started. Serial port: " << serial_port << "\n";
    uint8_t read_buf [256];
    cout << "Buff Created\n";
    while(1){
        cout << "Loop...\n";
        int n = read(serial_port, &read_buf, sizeof(read_buf));
        cout << "readed: " << n << "\n";
        for(int i = 0;i<n;i++){
            serial_buffer.push(read_buf[i]);
        }
    }
}

void serial_init(){
    cout << "Opening serial port: " << serial_port_name << "\n";
    serial_port = open(serial_port_name.c_str(), O_RDWR);
    cout << "Opened serial port: " << serial_port_name << ", " << serial_port << "\n";
    struct termios tty;
    cout << "termios tty\n";
    if(tcgetattr(serial_port, &tty) != 0) {
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
    }
    cout << "Starting thread\n";
    std::thread t1(serial_thread);
    t1.detach();
    /*string msg = "Hello world\n";
    for(int i = 0;i<5;i++){
        write(serial_port, msg.c_str(), msg.length());
    }*/

    /*uint8_t read_buf [256];
    for(int i = 0;i<20;i++){
        int n = read(serial_port, &read_buf, sizeof(read_buf));
        cout << "Len: " << n << ": [";
        for(int j = 0;j<n;j++){
            cout.setf(ios::hex, ios::basefield);
            cout << (int)read_buf[j];
            cout.unsetf(ios::hex);
            if(j != n-1) cout << ", ";
        }
        cout << "]\n";
    }
    close(serial_port);*/
}
void serial_write(std::string msg);

uint8_t serial_read(){
    return serial_buffer.pop();
}
bool serial_available(){
    return !serial_buffer.isEmpty();
}