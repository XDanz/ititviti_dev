//
// Created by danter on 2017-04-10.
//

#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <MessageInfo.h>
#include <chrono>
#include <iostream>
#include "RTClient.h"
#include "RTPeer.h
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
    for (uint64_t i = 0; i < cnt; i++) {
        Encoder::EncodeIntBigEndian(out, i,0,sizeof(uint64_t));
        double start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        messages.insert(std::pair<uint64_t, double>{i, start});
        Writen(sockfd,out, sizeof(uint64_t));

        Readn(sockfd, in, sizeof(uint64_t));
        double end = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        uint64_t val = Decoder::DecodeIntBigEndian(in,0, sizeof(uint64_t));
        std::map<uint64_t,double>::iterator iterator;
        iterator = messages.find(val);
        if (iterator != messages.end()) {
            std::cout << "RT" << iterator->second - end << " millis";
        }
    }


}