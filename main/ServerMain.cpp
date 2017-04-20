//
// Created by danter on 2017-04-10.
//
#include <string>
#include <iostream>
#include <EchoServer.h>
#include <ServerSocketImpl.h>

int
main(int argc, char **argv)
{
    ServerSocketImpl serverSocket{};
    uint16_t port;
    if (argc != 3) {
        std::cerr << "usage: server_start <IPaddress> <port>" << std::endl;
        exit(1);
    }

    if ((port = uint16_t(atoi(argv[2]))) == 0) {
        std::cerr << "'" << argv[2] << "' is not a number!" << std::endl;
        exit(1);
    }

    try {
        EchoServer server {serverSocket, std::string{argv[1]}, port};
        server.start();
    } catch (std::runtime_error &exception) {
        std::cerr << exception.what() << std::endl;
    }

}
