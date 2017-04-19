/**
 * @file   IOUtil.h
 * @Author Daniel Terranova (daniel.terranova@gmail.com)
 * @date   April, 2017
 * @brief  File contains implementation of Input/Output utility functions
 */

#ifndef ITIVITI_DEV_IOUTIL_H
#define ITIVITI_DEV_IOUTIL_H

#include <sys/socket.h>
#include <stdexcept>
#include <syslog.h>
#include <cstring>
#include <arpa/inet.h>
#include <cerrno>
#include <unistd.h>
#include <sys/poll.h>
#include <stdarg.h>
#include "ErrorUtil.h"
class SocketUtil
{
public:

    const void
    static Writen(int fd, void *ptr, size_t nbytes)
    {
        if (writen(fd, ptr, nbytes) != nbytes)
            throw std::runtime_error(ErrorUtil::err_sys("writen error"));
    }

    ssize_t
    static Readn(int fd, void* ptr, size_t nbytes)
    {
        ssize_t		n;

        if ( (n = readn(fd, ptr, nbytes)) < 0)
            throw std::runtime_error(ErrorUtil::err_sys("readn error"));
        return(n);
    }

    /**
      * @Brief waits for one of a set of file descriptors to become ready
      * to perform I/O
      * @return number of file descriptors ready to perform I/O
      */
    int
    static Poll(struct pollfd *fdarray, unsigned long nfds, int timeout)
    {
        int n;

        if ( (n = poll(fdarray, nfds, timeout)) < 0)
            throw std::runtime_error(ErrorUtil::err_sys("poll error"));

        return(n);
    }


    void
    static Close(int fd)
    {
        if (close(fd) == -1)
            throw std::runtime_error(ErrorUtil::err_sys("close error"));
    }
private:
    ssize_t						/* Write "n" bytes to a descriptor. */
    static writen(int fd, const void *vptr, size_t n)
    {
        size_t		nleft;
        ssize_t		nwritten;
        const char	*ptr;

        ptr = (const char *)vptr;
        nleft = n;
        while (nleft > 0) {
            if ( (nwritten = write(fd, ptr, nleft)) <= 0) {
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


    ssize_t						/* Read "n" bytes from a descriptor. */
    static readn(int fd, void *vptr, size_t n)
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
};
#endif //ITIVITI_DEV_IOUTIL_H
