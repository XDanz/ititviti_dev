/**
 * @file   EchoServer.cpp
 * @Author Daniel Terranova (daniel.terranova@gmail.com)
 * @date   April, 2017
 * @brief  File contains definitions of the TCP Echo server member function.
 *
 */

#include <netinet/in.h>
#include <string.h>
#include <sys/poll.h>
#include <cstdlib>
#include <unistd.h>
#include <stdexcept>
#include <SocketUtil.h>
#include "EchoServer.h"

void EchoServer::start()
{
    int nready = 0; // The number fo file descriptors ready for I/O
    int connfd, sockfd;
    ssize_t n;
    for (;;)
    {
        /**
         * waits for one of a set of file descriptors to become ready
         * to perform I/O
         */
        nready = SocketUtil::Poll(client, maxi+1UL, INFTIM);

        /**
         * data may be read on listening file descriptor which means
         * that new client has connected
         */
        if (isAcceptable())
        {    /** handle new client **/
            clilen = sizeof(cliaddr);
            connfd = serverSocket.Accept((sockaddr*) &cliaddr, &clilen);

            store_clientfd(connfd);
            if (--nready <= 0)
                continue;                /** no more readable descriptors **/
        }

        for (i = 1; i <= maxi; i++)
        {    /** check all clients for data **/
            if ( (sockfd = client[i].fd) < 0)
                continue;

            if (isReadable(i))
            {    /** Read/Write event or error */
                if ( (n = read(sockfd, buf, MAXLINE)) < 0)
                {
                    if (errno == ECONNRESET)
                    {
                        clientAborted(i);
                    }
                    else
                        ErrorUtil::err_sys("read error");
                }
                else if (n == 0)
                {
                    clientClosed(i);
                } else
                    SocketUtil::Writen(sockfd, buf, n);

                if (--nready <= 0)
                    break;                /** no more readable descriptors **/
            }
        }
    }
}

