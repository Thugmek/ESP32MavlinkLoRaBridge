#include <cstdint>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>

#include "../../config.h"

using namespace std;

void hal_delay(uint16_t ms){
    usleep(ms*1000);
}

void hal_debug(std::string msg){
    cout << msg << "\n";
}

void serial_emulator_loop(){
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (struct sockaddr*)&serverAddress,sizeof(serverAddress));
    listen(serverSocket, 5);
    int clientSocket = accept(serverSocket, nullptr, nullptr);

    char buffer[1024] = { 0 };
    while(1){
        // recieving data
        recv(clientSocket, buffer, sizeof(buffer), 0);
        cout << "Message from client: " << buffer << endl;
    }
    // closing the socket.
    close(serverSocket);
}

std::thread* serial_thread;

void serial_init(){
    serial_thread = new std::thread(serial_emulator_loop);
}
void serial_write(std::string msg);
void serial_read();