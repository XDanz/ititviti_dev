//
// Created by danter on 2017-04-10.
//

#ifndef ITIVITI_DEV_RTCLIENT_H
#define ITIVITI_DEV_RTCLIENT_H

#include <sys/socket.h>
#include <string>
#include <map>
#include "RTPeer.h"
#include <chrono>
#include <string.h>
#include <arpa/inet.h>

class RTClient: public RTPeer {
public:
    /**
     * Constructor to initiate RTClient
     *
     * @param host string containing an IPv4 network address in dotted-decimal
     * format to connect to
     * @param port TCP port corresponding the listening host to which connect to
     * @param cnt Number of messages to produce
     */
    RTClient(const std::string& host, int port, int cnt): host(host),
                                                          port(port), cnt(cnt) {
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

    };
    /**!
     * Start producing messages to the listening service
      * Calculate and display the round	trip time in milliseconds for each message
      */
    void start();
private:
    void* producer_thread();
    const std::string& host;
    int port;
    uint64_t cnt; // Number of messages to send
    // Each message is associated with a start clock to be able to count
    // the round trip time
    std::map<uint64_t,std::chrono::steady_clock::time_point> messages;
    double millis_diff(std::chrono::steady_clock::time_point end, std::chrono::steady_clock::time_point start);
    double avg = 0; // The average multiplied by the cnt
    double elapsed = 0;
    int sockfd;
};
#endif //ITIVITI_DEV_RTCLIENT_H
