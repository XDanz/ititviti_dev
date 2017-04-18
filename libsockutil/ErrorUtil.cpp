//
// Created by danter on 2017-04-10.
//
#include <stdio.h>
#include <cstdlib>
#include <errno.h>
#include <cstring>
#include <stdarg.h>
#include <unistd.h>
#include "ErrorUtil.h"

std::string
ErrorUtil::err_sys(const char *fmt, ...)
{
    va_list		ap;
    va_start(ap, fmt);
    std::string errMsg = err_doit(1,fmt, ap);
    va_end(ap);
    return errMsg;
}

std::string ErrorUtil::err_doit(int errnoflag, const char *fmt, va_list ap)
{
    int MAXLINE = 4096;
    int		errno_save, n;
    char	buf[MAXLINE + 1];

    errno_save = errno;		/* value caller might want printed */
    vsnprintf(buf, MAXLINE, fmt, ap);
    n = strlen(buf);
    if (errnoflag)
        snprintf(buf + n, MAXLINE - n, ": %s", strerror(errno_save));
    strcat(buf, "\n");

    return std::string(buf);
}

void
ErrorUtil::Close(int fd)
{
    if (close(fd) == -1)
        err_sys("close error");
}
