//
// Created by danter on 2017-04-10.
//
#include <stdio.h>
#include <syslog.h>
#include <cstdlib>
#include <errno.h>
#include <cstring>
#include <stdarg.h>
#include <unistd.h>
#include "RTPeer.h"

void
RTPeer::err_sys(const char *fmt, ...)
{
    va_list		ap;
    va_start(ap, fmt);
    err_doit(1, LOG_ERR, fmt, ap);
    va_end(ap);
    exit(1);
}

std::string RTPeer::err_doit(int errnoflag, int level, const char *fmt, va_list ap)
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

void
RTPeer::err_quit(const char *fmt, ...)
{
    va_list		ap;
    va_start(ap, fmt);
    err_doit(0, LOG_ERR, fmt, ap);
    va_end(ap);
    exit(1);
}

void
RTPeer::Close(int fd)
{
    if (close(fd) == -1)
        err_sys("close error");
}
