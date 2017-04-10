#include <RTClient.h>
//
// Created by danter on 2017-04-10.
//
int
main(int argc, char **argv)
{
     int cnt = 0;
     RTClient client {std::string{"127.0.0.1"}, 4179, cnt};
     client.start();





}




