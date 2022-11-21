#include "server.h"

#include <iostream>

Server::Server(): started(false), opts_({"127.0.0.1", 8080})
{}

void Server::run() {
    std::cout << "Server run" << std::endl;
}
