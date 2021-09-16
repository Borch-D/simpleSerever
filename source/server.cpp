#include "server.h"

Server::Server(char *path, char *port) : pathRoot(path), portCount(atoi(port)) {}

bool Server::Start() {
    if (!fs::exists(pathRoot)) {
        std::cout << "Directory not exist!" << std::endl;
        return false;
    }

    this->listenerSock = socket(AF_INET, SOCK_STREAM, 0);
    if (listenerSock < 0) {
        std::cout << "Socket error!" << std::endl;
        return false;
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(this->portCount);
    address.sin_addr.s_addr = inet_addr("192.168.0.2");
    if (bind(listenerSock, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::cout << "Port error!" << std::endl;
        return false;
    }

    std::cout << "Server address: 192.168.0.2" << std::endl <<
    "Port number: " << this->portCount << std::endl <<
    "Directory: " << this->pathRoot << std::endl;

    listen(listenerSock, 1);
    return true;
}

bool Server::Listen() {
    while(true) {
        int socket = accept(this->listenerSock, NULL, NULL);
        if(socket < 0) {
            std::cout << "Error!" << std::endl;
            return false;
        }

        while(true) {
            int bytes_read = recv(socket, buffer, sizeof (buffer), 0);
            if(bytes_read <= 0)
                break;
            process();
        }
        close(socket);
    }
}

void Server::process() {
    char *command, *path, *fileName;
    command = strtok(this->buffer, " ");
    path = strtok(NULL, " ");
    fileName = strtok(NULL, "\0");
    if (strcmp(command, "c") == 0) {
        bool success = createFile(path, fileName);
        if (success)
            std::cout << "File was created!" << std::endl;
    }
    else if(strcmp(command, "d") == 0) {
        bool success = deleteFile(path, fileName);
        if (success)
            std::cout << "File was deleted!" << std::endl;
    }
    else {
        std::cout << "Error command!" << std::endl;
    }
}

bool Server::createFile(char *path, char *filename) {
    char currentPath[50];
    strcpy(currentPath, this->pathRoot);
    strcat(currentPath, path);
    fs::path directory = currentPath;
    if (!fs::exists(directory)){
        fs::create_directories(directory);
    }
    strcat(currentPath, filename);
    std::ofstream f(currentPath);
    f.close();
    return true;
}

bool Server::deleteFile(char *path, char *filename) {
    char currentPath[50];
    strcpy(currentPath, this->pathRoot);
    strcat(currentPath, path);
    strcat(currentPath, filename);
    fs::path filePath = currentPath;
    if (!fs::exists(filePath)){
        std::cout << "File not exist!" << std::endl;
        return false;
    }
    fs::remove(filePath);
    return true;
}

Server::~Server() {
    close(this->listenerSock);
}

