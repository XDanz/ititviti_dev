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
#include "GenericSocket.h"

class IServerSocket: public GenericSocket {
public:
    virtual void Bind(const struct sockaddr *sa, socklen_t salen) = 0;
    virtual void Listen(int backlog) = 0;
    virtual int Accept(struct sockaddr *sa, socklen_t *salenptr) = 0;
};
#endif //ITIVITI_DEV_ISERVERSOCKET_H
