#include <cstdint>
#include <stdio.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
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
// LoRa =======================================================================
bool LoRa_server = false;
void select_LoRa_socket_role(bool server){
    LoRa_server = server;
}

void LoRa_init_server(){
    int server_socket;
    int client_socket;
    struct sockaddr_un server_addr;
    struct sockaddr_un client_addr;

    server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
	if( -1 == server_socket )
	{
		hal_debug("Error on socket() call \n");
		return;
	}

    server_addr.sun_family = AF_UNIX;
	strcpy( server_addr.sun_path, "LoRaMockupSocket" );
	unlink(server_addr.sun_path);
    int len = 0;
	len = strlen(server_addr.sun_path) + sizeof(server_addr.sun_family);
	if( bind(server_socket, (struct sockaddr*)&server_addr, len) != 0)
	{
		hal_debug("Error on binding socket \n");
		return;
	}

    if( listen(server_socket, 1) != 0 )
	{
		hal_debug("Error on listen call \n");
	}

    unsigned int sock_len = 0;
    hal_debug("Waiting for connection.... \n");
    if( (client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &sock_len)) == -1 )
    {
        hal_debug("Error on accept() call \n");
        return;
    }

}

void LoRa_init_client(){

}

void LoRa_init(){
    if(LoRa_server){
        LoRa_init_server();
    }else{
        LoRa_init_client();
    }
}

void LoRa_send_message(uint8_t *data, uint8_t len){

}

// Serial =====================================================================
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