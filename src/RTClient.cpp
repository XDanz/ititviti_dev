//
// Created by danter on 2017-04-10.
//

#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <chrono>
#include <iostream>
#include <iomanip>
#include "RTClient.h"
#include "RTPeer.h"
#include "Encoder.h"
#include "Decoder.h"


void RTClient::start()
{
    int					sockfd, n, counter = 0;
    char				recvline[MAXLINE + 1];
    struct sockaddr_in	servaddr;

    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_sys("socket error");

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(port);
    if (inet_pton(AF_INET, host.c_str(), &servaddr.sin_addr) <= 0)
        err_quit("inet_pton error for %s", host.c_str());

    if (connect(sockfd, (sockaddr *) &servaddr, sizeof(servaddr)) < 0)
        err_sys("connect error");

    uint8_t out[sizeof(uint64_t)];
    uint8_t in[sizeof(uint64_t)];
    Encoder encoder;
    Decoder decoder;
    for (uint64_t i = 0; i < cnt; i++) {
        encoder.EncodeIntBigEndian(out, i,0,sizeof(uint64_t));
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        messages.insert(std::pair<uint64_t, std::chrono::steady_clock::time_point>{i, begin});
        Writen(sockfd,out, sizeof(uint64_t));
        //sleep(1);
        Readn(sockfd, in, sizeof(uint64_t));

        std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();

        uint64_t val = decoder.DecodeIntBigEndian(in,0, sizeof(uint64_t));
        std::map<uint64_t,std::chrono::steady_clock::time_point>::iterator iterator;
        iterator = messages.find(val);
        if (iterator != messages.end()) {
            std::cout << "RT = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - iterator->second).count()/double(1000000) << " millis" << std::endl;
        }
    }
}