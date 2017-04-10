//
// Created by danter on 2017-04-10.
//
#include <string>
#include "EchoServer.h"
int
main(int argc, char **argv)
{

    EchoServer server {std::string{"127.0.0.1"}, 4179};
    server.start();

}
