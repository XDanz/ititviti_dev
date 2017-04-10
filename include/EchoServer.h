//
// Created by danter on 2017-04-10.
//

#ifndef ITIVITI_DEV_ECHOSERVER_H
#define ITIVITI_DEV_ECHOSERVER_H

#include <sys/socket.h>
#include <string>

class EchoServer: public RTPeer {

public:
    void start();
    EchoServer(const std::string& host, int port): serverHost(host), serverPort(port) { };
protected:

    const int serverPort;	/* max text line length */
    const std::string& serverHost;
    const int  LISTENQ = 1024;
    const int  INFTIM  = (-1);
private:
    int Poll(struct pollfd *fdarray, unsigned long nfds, int timeout);
    //void err_sys(const char *fmt, ...);
    //void err_doit(int errnoflag, int level, const char *fmt, va_list ap);
    void Bind(int fd, const struct sockaddr *sa, socklen_t salen);
    void Listen(int fd, int backlog);
    int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr);
    //void err_quit(const char *fmt, ...);
    //void Close(int fd);

    const char * Inet_ntop(int family, const void *addrptr, char *strptr, size_t len);
    void Inet_pton(int family, const char *strptr, void *addrptr);

};

#endif //ITIVITI_DEV_ECHOSERVER_H
