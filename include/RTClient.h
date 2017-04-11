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

class RTClient: public RTPeer {
public:
    RTClient(const std::string& host, int port, int cnt): host(host),
                                                          port(port), cnt(cnt) { };
    void start();
private:
    const std::string& host;
    int port;
    uint64_t cnt;
    std::map<uint64_t,std::chrono::steady_clock::time_point> messages;
};
#endif //ITIVITI_DEV_RTCLIENT_H
