//
// Created by danter on 2017-04-12.
//

#ifndef ITIVITI_DEV_SOCKAPI_H
#define ITIVITI_DEV_SOCKAPI_H

#include <sys/socket.h>
#include <stdexcept>
#include <syslog.h>
#include <cstring>
#include <arpa/inet.h>
#include <cerrno>
#include <unistd.h>
#include <stdarg.h>
#include "SocketUtil.h"
#include "GenericSocket.h"

class IClientSocket: public GenericSocket {
public:
    IClientSocket() {}
    virtual ~IClientSocket() {}
    virtual void connectSocket(sockaddr* sockaddr, socklen_t socklen) = 0;
    virtual void writeToSocket(void* ptr, size_t nbytes) = 0;
    virtual void setAddr(const std::string host, void* buf) = 0;
    virtual ssize_t readFromSocket(void* ptr, size_t nbytes) = 0;
};

#endif //ITIVITI_DEV_SOCKAPI_H
