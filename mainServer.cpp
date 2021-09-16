#include "server.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Not find port or path to directory!" << std::endl;
        return 1;
    }

    Server server = Server(argv[1], argv[2]);
    if (!server.Start())
        return 1;
    if (!server.Listen())
        return 1;
    return 0;
}

