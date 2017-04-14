//
// Created by danter on 2017-04-14.
//

#ifndef ITIVITI_DEV_CLIENTSOCKETIMPL_H
#define ITIVITI_DEV_CLIENTSOCKETIMPL_H

#include <bits/socket.h>
#include <sys/socket.h>
#include <stdexcept>
#include <syslog.h>
#include <cstring>
#include <arpa/inet.h>
#include <cerrno>
#include <unistd.h>
#include <stdarg.h>
#include "IOUtil.h"
#include "ISocket.h"
#include "IClientSocket.h"

class ClientSocketImpl: public IClientSocket {

    void connectSocket(sockaddr* sockaddr, socklen_t socklen) override
    {
        if (connect(this->sockfd, sockaddr, socklen) < 0)
            throw std::runtime_error(ErrorUtil::err_sys("Connect error"));
    }

    void setAddr(const std::string host, void* buf)
    {
        if (inet_pton(AF_INET, host.c_str(), buf) <=0 )
            throw std::runtime_error(ErrorUtil::err_sys("inet_pton error for %s", host.c_str()));
    }

    const void
    writeToSocket(void* ptr, size_t nbytes)
    {   IOUtil::Writen(this->sockfd, ptr, nbytes); }

    ssize_t readFromSocket(void* ptr, size_t nbytes) override
    { return IOUtil::Readn(this->sockfd, ptr, nbytes); }

    int tt() { return 1;}

    int tv(int x) { return x;}
};
#endif //ITIVITI_DEV_CLIENTSOCKETIMPL_H
