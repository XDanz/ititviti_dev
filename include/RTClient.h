//
// Created by danter on 2017-04-10.
//

#ifndef ITIVITI_DEV_RTCLIENT_H
#define ITIVITI_DEV_RTCLIENT_H

#include <sys/socket.h>
#include <string>
#include <map>

class RTClient: public RTPeer {
public:
    RTClient(const std::string& host, int port, int cnt): serverHost(host),
                                                          serverPort(port), cnt(cnt) { };
    void start();
private:
    const std::string& host;
    int port;
    uint64_t cnt;
    std::map<uint64_t,double> messages;
};
#endif //ITIVITI_DEV_RTCLIENT_H
