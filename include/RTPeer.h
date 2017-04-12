//
// Created by danter on 2017-04-10.
//

#ifndef ITIVITI_DEV_RTPEER_H
#define ITIVITI_DEV_RTPEER_H

#include <stdio.h>
#include <string>

class RTPeer {

protected:
    static const int MAXLINE = 4096;	/* max text line length */
    static void err_sys(const char *fmt, ...);
    static std::string err_doit(int errnoflag, int level, const char *fmt, va_list ap);
    static void err_quit(const char *fmt, ...);
    static void Close(int fd);
    static void Writen(int fd, void *ptr, size_t nbytes);
    static ssize_t Readn(int fd, void *ptr, size_t nbytes);
};

#endif //ITIVITI_DEV_RTPEER_H
