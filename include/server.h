#ifndef SIMPLESERVER_SERVER_H
#define SIMPLESERVER_SERVER_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <filesystem>
#include <cstring>
#include <fstream>

namespace fs = std::filesystem;

class Server {
private:
    int listenerSock;
    struct sockaddr_in address;
    const char *pathRoot;
    unsigned int portCount;
    char buffer[100];
    void process();
    bool createFile(char*, char*);
    bool deleteFile(char*, char*);
public:
    Server(char*, char*);
    bool Start();
    bool Listen();
    ~Server();
};

#endif //SIMPLESERVER_SERVER_H
