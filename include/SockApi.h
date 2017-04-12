//
// Created by danter on 2017-04-12.
//

#ifndef ITIVITI_DEV_SOCKAPI_H
#define ITIVITI_DEV_SOCKAPI_H
#include <bits/socket.h>
#include <sys/socket.h>
#include <stdexcept>
#include <syslog.h>
#include <cstring>
#include <arpa/inet.h>

class SockApi {
public:
    virtual ~SockApi() {}
    virtual int createSocket() = 0;
    virtual void connectfd(int sockfd, sockaddr * sockaddr, socklen_t socklen) = 0;
    virtual void Writen(int fd, void *ptr, size_t nbytes) = 0;
    virtual void setAddr(const std::string host, void* buf) = 0;
    virtual void Readn(int fd, void *ptr, size_t nbytes) = 0;
};

class BsdSockApi: public SockApi {
    int const MAXLINE = 1024;
    int createSocket() override
    {
        int sockfd;
        if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
            throw std::runtime_error("socket error");
        return sockfd;
    }
    void connectfd(int sockfd, sockaddr* sockaddr, socklen_t socklen) override
    {
        if (connect(sockfd, sockaddr, socklen) < 0)
            throw std::runtime_error(err_sys("Connect error"));
    }

    void setAddr(const std::string host, void* buf)
    {
        if (inet_pton(AF_INET, host.c_str(), buf) <=0 )
            throw std::runtime_error(err_sys("inet_pton error for %s", host.c_str()));
    }

    void Writen(int fd, void* ptr, size_t nbytes) override
    {

    }
    void Readn(int fd, void* ptr, size_t nbytes) override
    {

    }
    int sockfd;

    std::string
    err_sys(const char *fmt, ...)
    {
        va_list		ap;
        va_start(ap, fmt);
        err_doit(1, LOG_ERR, fmt, ap);
        va_end(ap);
        exit(1);
    }

    std::string err_doit(int errnoflag, int level, const char *fmt, va_list ap)
    {
        int		errno_save, n;
        char	buf[MAXLINE + 1];

        errno_save = errno;		/* value caller might want printed */
        vsnprintf(buf, MAXLINE, fmt, ap);	/* safe */
        n = strlen(buf);
        if (errnoflag)
            snprintf(buf + n, MAXLINE - n, ": %s", strerror(errno_save));
        strcat(buf, "\n");

        fflush(stdout);		/* in case stdout and stderr are the same */
        fputs(buf, stderr);
        fflush(stderr);

        return std::string(buf);
    }
};
#endif //ITIVITI_DEV_SOCKAPI_H
