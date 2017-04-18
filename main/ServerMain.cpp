//
// Created by danter on 2017-04-10.
//
#include <string>
#include <iostream>
#include <EchoServer.h>
#include <IServerSocket.h>
#include "../librtserver/EchoServer.h"
int
main(int argc, char **argv)
{
    ServerSocketImpl serverSocket{};
    int port;
    if (argc != 3) {
        std::cerr << "usage: server_start <IPaddress> <port>" << std::endl;
        exit(1);
    }

    if ((port = atoi(argv[2])) == 0) {
        std::cerr << "'" << argv[2] << "' is not a number!" << std::endl;
        exit(1);
    }

    EchoServer server {serverSocket, std::string{argv[1]}, port};
    server.start();

}