/**
 * @file   IServerSocket.h
 * @Author Daniel Terranova (daniel.terranova@gmail.com)
 * @date   April, 2017
 * @brief  File contains implementation of the tcp server socket.
 */

#ifndef ITIVITI_DEV_ISERVERSOCKET_H
#define ITIVITI_DEV_ISERVERSOCKET_H

#include <netinet/in.h>
#include <string.h>
#include <sys/poll.h>
#include <cstdlib>
#include "ErrorUtil.h"
#include <cerrno>
#include <unistd.h>
#include <stdexcept>
#include "ISocket.h"

class IServerSocket: public ISocket {
public:
    virtual void Bind(const struct sockaddr *sa, socklen_t salen) = 0;
    virtual void Listen(int backlog) = 0;
    virtual int Accept(struct sockaddr *sa, socklen_t *salenptr) = 0;
};

class ServerSocketImpl: public IServerSocket {

    void
    Bind(const struct sockaddr *sa, socklen_t salen) override
    {
        if (bind(this->sockfd, sa, salen) < 0)
            throw std::runtime_error(ErrorUtil::err_sys("bind error"));
    }

    void
    Listen(int backlog)
    {
        if (listen(this->sockfd, backlog) < 0)
            throw std::runtime_error(ErrorUtil::err_sys("listen error"));
    }

    int
    Accept(struct sockaddr *sa, socklen_t *salenptr) override
    {
        int n;

        again:
        if ( (n = accept(this->sockfd, sa, salenptr)) < 0) {
            if (errno == EPROTO || errno == ECONNABORTED)
                goto again;
            else
                throw std::runtime_error(ErrorUtil::err_sys("accept error"));
        }
        return(n);
    }
};


#endif //ITIVITI_DEV_ISERVERSOCKET_H
