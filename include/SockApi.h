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
#include <cerrno>
#include <unistd.h>
#include <stdarg.h>

class SockApi {
public:
    virtual ~SockApi() {}
    virtual void createSocket() = 0;
    virtual void connectfd(sockaddr * sockaddr, socklen_t socklen) = 0;
    virtual const void Writen(void *ptr, size_t nbytes) = 0;
    virtual void setAddr(const std::string host, void* buf) = 0;
    virtual ssize_t Readn(void *ptr, size_t nbytes) = 0;
};

class SockApiImpl: public SockApi {
    int const MAXLINE = 1024;

    void createSocket() override
    {
        int sockfd;
        if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
            throw std::runtime_error("socket error");
        this->sockfd = sockfd;
    }

    void connectfd(sockaddr* sockaddr, socklen_t socklen) override
    {
        if (connect(this->sockfd, sockaddr, socklen) < 0)
            throw std::runtime_error(err_sys("Connect error"));
    }

    void setAddr(const std::string host, void* buf)
    {
        if (inet_pton(AF_INET, host.c_str(), buf) <=0 )
            throw std::runtime_error(err_sys("inet_pton error for %s", host.c_str()));
    }

    ssize_t						/* Write "n" bytes to a descriptor. */
    writen(const void *vptr, size_t n)
    {
        size_t		nleft;
        ssize_t		nwritten;
        const char	*ptr;

        ptr = (const char *)vptr;
        nleft = n;
        while (nleft > 0) {
            if ( (nwritten = write(sockfd, ptr, nleft)) <= 0) {
                if (nwritten < 0 && errno == EINTR)
                    nwritten = 0;		/* and call write() again */
                else
                    return(-1);			/* error */
            }

            nleft -= nwritten;
            ptr   += nwritten;
        }
        return(n);
    }
/* end writen */

    const void
    Writen(void *ptr, size_t nbytes)
    {
        if (writen(ptr, nbytes) != nbytes)
            err_sys("writen error");
    }

    ssize_t Readn(void* ptr, size_t nbytes) override
    {
        ssize_t		n;

        if ( (n = readn(sockfd, ptr, nbytes)) < 0)
            throw std::runtime_error(err_sys("readn error"));
        return(n);
    }
    ssize_t						/* Read "n" bytes from a descriptor. */
    readn(int fd, void *vptr, size_t n)
    {
        size_t	nleft;
        ssize_t	nread;
        char	*ptr;

        ptr = (char	*)vptr;
        nleft = n;
        while (nleft > 0) {
            if ( (nread = read(fd, ptr, nleft)) < 0) {
                if (errno == EINTR)
                    nread = 0;		/* and call read() again */
                else
                    return(-1);
            } else if (nread == 0)
                break;				/* EOF */

            nleft -= nread;
            ptr   += nread;
        }
        return(n - nleft);		/* return >= 0 */
    }
/* end readn */

    int sockfd = 0;

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
