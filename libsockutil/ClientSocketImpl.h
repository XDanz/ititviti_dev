//
// Created by danter on 2017-04-14.
//

#ifndef ITIVITI_DEV_CLIENTSOCKETIMPL_H
#define ITIVITI_DEV_CLIENTSOCKETIMPL_H

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
#include "IClientSocket.h"

class ClientSocketImpl: public IClientSocket {

    void
    connectSocket(sockaddr* sockaddr, socklen_t socklen) override
    {
        if (connect(this->sockfd, sockaddr, socklen) < 0)
            throw std::runtime_error(ErrorUtil::err_sys("Connect error"));
    }

    void
    setAddr(const std::string host, void* buf)
    {
        if (inet_pton(AF_INET, host.c_str(), buf) <=0 )
            throw std::runtime_error(ErrorUtil::err_sys("inet_pton error for %s", host.c_str()));
    }

    void
    writeToSocket(void* ptr, size_t nbytes)
    {   SocketUtil::Writen(this->sockfd, ptr, nbytes); }

    ssize_t readFromSocket(void* ptr, size_t nbytes) override
    { return SocketUtil::Readn(this->sockfd, ptr, nbytes); }

};
#endif //ITIVITI_DEV_CLIENTSOCKETIMPL_H
