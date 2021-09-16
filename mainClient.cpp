#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <cstring>


int main(int argc, char* argv[])
{
    if (argc != 6) {
        std::cout << "1 - Server address" << std::endl <<
                  "2 - Port number" << std::endl <<
                  "3 - Command: c(create) or d(delete)" << std::endl <<
                  "4 - Path" << std::endl <<
                  "5 - File name" << std::endl;
        return 1;
    }
    int sock;
    struct sockaddr_in address;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        std::cout << "Socket error!" << std::endl;
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(atoi(argv[2]));
    address.sin_addr.s_addr = inet_addr(argv[1]);
    if(connect(sock, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        std::cout << "Connect error!" << std::endl;
        return 1;
    }

    char message[100];
    strcpy(message, argv[3]);
    strcat(message, " ");
    strcat(message, argv[4]);
    strcat(message, " ");
    strcat(message, argv[5]);
    send(sock, message, sizeof(message), 0);

    close(sock);

    return 0;
}
