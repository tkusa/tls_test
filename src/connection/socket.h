#include <iostream>

using namespace std;

#ifndef SOCKET_H
#define SOCKET_H

namespace Connection
{

    class Socket 
    {
        public:
            int sock;
            int connection_fd;
            char buffer[8196] = { 0 };
            int create(int port);
            int serve();
            string receive();
            int finish();
    };
}

#endif
