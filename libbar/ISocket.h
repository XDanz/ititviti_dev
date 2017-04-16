//
// Created by danter on 2017-04-14.
//

#ifndef ITIVITI_DEV_ISOCKET_H
#define ITIVITI_DEV_ISOCKET_H


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
#include <zconf.h>
#include <stdexcept>
#include "ErrorUtil.h"

class ISocket {
public:
    ISocket() { }
    virtual void createSocket()
    {
        if ( (this->sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
            throw std::runtime_error("socket error");
    }

    virtual void
    Close()
    {
        if (close(this->sockfd) == -1)
            throw std::runtime_error(ErrorUtil::err_sys("close error"));
    }

    int getSockfd() const
    {
        return sockfd;
    }
protected:
    int sockfd;
};

#endif //ITIVITI_DEV_ISOCKET_H
