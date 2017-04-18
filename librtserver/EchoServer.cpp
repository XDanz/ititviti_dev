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
#include <IOUtil.h>
#include "EchoServer.h"

void EchoServer::start() 
{
    int i, maxi, connfd, sockfd;
    int nready;
    ssize_t n;
    int MAXLINE = 4096;	/* max text line length */
    char buf[MAXLINE];
    socklen_t clilen;
    struct pollfd client[FOPEN_MAX];
    struct sockaddr_in cliaddr, servaddr;

    serverSocket.createSocket();

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    Inet_pton(AF_INET, serverHost.c_str(), &servaddr.sin_addr.s_addr);
    servaddr.sin_port = htons(serverPort);

    serverSocket.Bind((sockaddr *) & servaddr, sizeof(servaddr));

    serverSocket.Listen(LISTENQ);

    client[0].fd = serverSocket.getSockfd();
    client[0].events = POLLRDNORM;
    for (i = 1; i<FOPEN_MAX; i++)
        client[i].fd = -1;        /* -1 indicates available entry */
    maxi = 0;                    /* max index into client[] array */

    for (;;) 
    {
        nready = IOUtil::Poll(client, maxi+1, INFTIM);
        /**
         * data may be read on listening file descriptor which means
         * that new client has connected
         */
        if (client[0].revents & POLLRDNORM)
        {    /** handle new client **/
            clilen = sizeof(cliaddr);
            connfd = serverSocket.Accept((sockaddr*) &cliaddr, &clilen);

            for (i = 1; i < FOPEN_MAX; i++)
            {
                if (client[i].fd < 0)
                {
                    /** save descriptor **/
                    client[i].fd = connfd;
                    break;
                }
            }

            if (i == FOPEN_MAX)
                throw std::runtime_error(ErrorUtil::err_sys("too many clients"));

            client[i].events = POLLRDNORM;
            if (i > maxi)
                maxi = i;                /** max index in client[] array **/

            if (--nready <= 0)
                continue;                /** no more readable descriptors **/
        }

        for (i = 1; i <= maxi; i++)
        {    /** check all clients for data **/
            if ( (sockfd = client[i].fd) < 0)
                continue;

            if (client[i].revents & (POLLRDNORM | POLLERR)) 
            {    /** Read/Write event or error */
                if ( (n = read(sockfd, buf, MAXLINE)) < 0)
                {
                    if (errno == ECONNRESET)
                    {
                        /** connection reset by client **/
                        printf("client[%d] aborted connection\n", i);
                        ErrorUtil::Close(sockfd);
                        client[i].fd = -1;
                    }
                    else
                        ErrorUtil::err_sys("read error");
                }
                else if (n == 0)
                {
                    /** connection closed by client **/
                    printf("client[%d] closed connection\n", i);
                    ErrorUtil::Close(sockfd);
                    client[i].fd = -1;
                } else
                    IOUtil::Writen(sockfd, buf, n);

                if (--nready <= 0)
                    break;                /** no more readable descriptors **/
            }
        }
    }
}

