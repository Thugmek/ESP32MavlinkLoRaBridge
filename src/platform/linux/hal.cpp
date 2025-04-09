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
#include <mutex>

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
std::mutex LoRa_mutex;
int LoRa_socket;
bool LoRa_data_available = false;
char LoRa_buff[256];

void select_LoRa_socket_role(bool server){
    LoRa_server = server;
}

void LoRa_receive_thread(int socket){
    char recv_buf[256];
    while(1){
        int data_recv = 0;
        data_recv = recv(socket, recv_buf, 256, 0);
        if(data_recv > 0){
            //cout << data_recv << ", " << recv_buf << "\n";
            LoRa_mutex.lock();
            memcpy(LoRa_buff, recv_buf, 256);
            LoRa_data_available = true;
            LoRa_mutex.unlock();
        }else if(data_recv < 0){
            cout << "Error on recv() call: " << data_recv << "\n";
        }
    }
}

void LoRa_send(uint8_t *data, uint16_t len){
    if( send(LoRa_socket, data, len, 0 ) == -1 )
    {
        hal_debug("Client: Error on send() call \n");
    }
}
uint16_t LoRa_receive(uint8_t *data){
    LoRa_mutex.lock();
    memcpy(data, LoRa_buff, 256);
    LoRa_data_available = false;
    LoRa_mutex.unlock();
    return 0;
}
bool LoRa_available(){
    return LoRa_data_available;
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

    std::thread t1(LoRa_receive_thread, client_socket);
    t1.detach();

    /*char send_buf[] = "Hello World";

    while(1){
        if( send(client_socket, send_buf, 12, 0 ) == -1 )
        {
            hal_debug("Client: Error on send() call \n");
        }
        hal_delay(500);
    }*/

    LoRa_socket = client_socket;

}

void LoRa_init_client(){
    int sock = 0;
	int data_len = 0;
	struct sockaddr_un remote;

	if( (sock = socket(AF_UNIX, SOCK_STREAM, 0)) == -1  )
	{
		hal_debug("Client: Error on socket() call \n");
		return;
	}

	remote.sun_family = AF_UNIX;
	strcpy( remote.sun_path, "LoRaMockupSocket" );
	data_len = strlen(remote.sun_path) + sizeof(remote.sun_family);

	hal_debug("Client: Trying to connect... \n");
	if( connect(sock, (struct sockaddr*)&remote, data_len) == -1 )
	{
		hal_debug("Client: Error on connect call \n");
		return;
	}

	hal_debug("Client: Connected \n");

    
    std::thread t1(LoRa_receive_thread, sock);
    t1.detach();

    LoRa_socket = sock;


    char send_buf[] = "Hello World";
    /*while(1){
        if( send(sock, send_buf, 12, 0 ) == -1 )
        {
            hal_debug("Client: Error on send() call \n");
        }
        hal_delay(500);
    }*/
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