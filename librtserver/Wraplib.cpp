/*
 * Wrapper functions for our own library functions.
 * Most are included in the source file for the function itself.
 */

#include "EchoServer.h"
#include "../libbar/ErrorUtil.h"
#include <arpa/inet.h>
#include <stdexcept>

void
EchoServer::Inet_pton(int family, const char *strptr, void *addrptr)
{
	int n;

	if ( (n = inet_pton(family, strptr, addrptr)) < 0)
		throw std::runtime_error(ErrorUtil::err_sys("inet_pton error for %s", strptr));	/* errno set */
	else if (n == 0)
		throw std::runtime_error(("inet_pton error for %s", strptr));	/* errno not set */
}
