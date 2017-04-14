/**
 * @file   EchoServer.h
 * @Author Daniel Terranova (daniel.terranova@gmail.com)
 * @date   April, 2017
 * @brief  File contains declaration of the TCP Echo server. The only purpose of this
 * class is to bind,listen and echo back request made from clients.
 *
 * The server is a single process that uses I/O multiplexing with poll() system call.
 * The reason to use poll() instead of multiple threads is to use one thread
 * that handle multiple client sockets (including the listening socket) and it suffice
 * for this solution.
 */

#ifndef ITIVITI_DEV_ECHOSERVER_H
#define ITIVITI_DEV_ECHOSERVER_H

#include <sys/socket.h>
#include <string>
#include "ErrorUtil.h"
#include "IServerSocket.h"

class EchoServer {

public:
    EchoServer(IServerSocket& serverSocket, const std::string& host, uint16_t port):
            serverSocket(serverSocket), serverHost(host), serverPort(port) { };
    void start();
protected:
    const uint16_t serverPort;
    const std::string& serverHost;
    const int  LISTENQ = 1024;
    const int  INFTIM  = (-1);
private:
    void Inet_pton(int family, const char *strptr, void *addrptr);
    IServerSocket& serverSocket;
};

#endif //ITIVITI_DEV_ECHOSERVER_H
