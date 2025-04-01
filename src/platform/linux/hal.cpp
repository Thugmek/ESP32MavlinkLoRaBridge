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

using namespace std;

void hal_delay(uint16_t ms){
    usleep(ms*1000);
}

void hal_debug(std::string msg){
    cout << msg << "\n";
}

void serial_init(){
    int serial_port = open("/dev/pts/4", O_RDWR);
    struct termios tty;
    if(tcgetattr(serial_port, &tty) != 0) {
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
    }
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_cflag |= CREAD | CLOCAL;
    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO; // Disable echo
    tty.c_lflag &= ~ECHOE; // Disable erasure
    tty.c_lflag &= ~ECHONL; // Disable new-line echo
    tty.c_lflag &= ~ISIG;
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);
    tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
    tty.c_cc[VTIME] = 10;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
    tty.c_cc[VMIN] = 0;
    cfsetispeed(&tty, B460800);
    cfsetospeed(&tty, B460800);
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
    }
    string msg = "Hello world\n";
    for(int i = 0;i<5;i++){
        write(serial_port, msg.c_str(), msg.length());
    }

    char read_buf [256];
    for(int i = 0;i<20;i++){
        int n = read(serial_port, &read_buf, sizeof(read_buf));
        cout << read_buf << "\n";
    }
    close(serial_port);
}
void serial_write(std::string msg);
void serial_read();