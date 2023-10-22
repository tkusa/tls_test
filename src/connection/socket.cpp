#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <unistd.h>

#include "socket.h"

using namespace std;
using namespace Connection;


int Socket::create(int port) {
    int s;
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    this->sock = socket(AF_INET, SOCK_STREAM, 0);
    if (this->sock < 0) {
        perror("Unable to create socket");
        exit(EXIT_FAILURE);
    }

    if (bind(this->sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Unable to bind");
        exit(EXIT_FAILURE);
    }

    if (listen(this->sock, 1) < 0) {
        perror("Unable to listen");
        exit(EXIT_FAILURE);
    }

    return this->sock;
}


int Socket::serve() {
    struct sockaddr_in addr;
    unsigned int len = sizeof(addr);
    this->connection_fd = accept(sock, (struct sockaddr*)&addr, &len);
    return this->connection_fd;
}

string Socket::receive() {
    read(this->sock, this->buffer, 8196);
    string str = this->buffer;
    return str;
}

int Socket::finish() {
    close(this->sock);
    shutdown(connection_fd, SHUT_RDWR);
    return 0;
}

