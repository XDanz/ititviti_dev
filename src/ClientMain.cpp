#include <RTClient.h>
#include <iostream>
#include <ClientSocketImpl.h>
//
// Created by danter on 2017-04-10.
//
int
main(int argc, char **argv)
{
     uint16_t port;
     uint64_t cnt;

     if (argc != 4)
     {
          std::cerr << "usage: client_start <IPaddress> <port> <num>" << std::endl;
          exit(1);
     }

     if ((port = uint16_t(atoi(argv[2]))) == 0)
     {
          std::cerr << "'" << argv[2] << "' is not a number!" << std::endl;
          exit(1);
     }

     if ((cnt = uint64_t(atoi(argv[3]))) == 0)
     {
          std::cerr << "'" << argv[3] << "' is not a number!" << std::endl;
          exit(1);
     }

     ClientSocketImpl sockApi{};
     RTClient client {sockApi, std::string{argv[1]}, port, cnt};
     client.start();
}




