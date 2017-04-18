//
// Created by danter on 2017-04-10.
//

#ifndef ITIVITI_DEV_RTPEER_H
#define ITIVITI_DEV_RTPEER_H

#include <stdio.h>
#include <string>

class ErrorUtil {

public:
    static std::string err_sys(const char *fmt, ...);
    static void Close(int fd);
private:
    static std::string err_doit(int errnoflag, const char *fmt, va_list ap);
};

#endif //ITIVITI_DEV_RTPEER_H
