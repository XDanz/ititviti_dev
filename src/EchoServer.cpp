#include <netinet/in.h>
#include <string.h>
#include <sys/poll.h>
#include <cstdlib>
#include "RTPeer.h
#include <cerrno>
#include <zconf.h>
#include "EchoServer.h"
//
// Created by danter on 2017-04-10.
//
typedef sockaddr SA;
int		daemon_proc;		/* set nonzero by daemon_init() */

int
EchoServer::Poll(struct pollfd *fdarray, unsigned long nfds, int timeout)
{
    int		n;

    if ( (n = poll(fdarray, nfds, timeout)) < 0)
        err_sys("poll error");

    return(n);
}


void
EchoServer::Bind(int fd, const struct sockaddr *sa, socklen_t salen)
{
    if (bind(fd, sa, salen) < 0)
        err_sys("bind error");
}

/* Fatal error related to system call
 * Print message and terminate */

/* include Listen */
void
EchoServer::Listen(int fd, int backlog)
{
    char	*ptr;

    /*4can override 2nd argument with environment variable */
    if ( (ptr = getenv("LISTENQ")) != NULL)
        backlog = atoi(ptr);

    if (listen(fd, backlog) < 0)
        err_sys("listen error");
}

int
EchoServer::Accept(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
    int		n;

    again:
    if ( (n = accept(fd, sa, salenptr)) < 0) {
#ifdef	EPROTO
        if (errno == EPROTO || errno == ECONNABORTED)
#else
            if (errno == ECONNABORTED)
#endif
            goto again;
        else
            err_sys("accept error");
    }
    return(n);
}




void EchoServer::start() {
    int i, maxi, listenfd, connfd, sockfd;
    int nready;
    ssize_t n;
    char buf[MAXLINE];
    socklen_t clilen;
    struct pollfd client[FOPEN_MAX];
    struct sockaddr_in cliaddr, servaddr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    Inet_pton(AF_INET, serverHost.c_str(), &servaddr.sin_addr.s_addr);
    servaddr.sin_port = htons(serverPort);

    Bind(listenfd, (SA*) & servaddr, sizeof(servaddr));

    Listen(listenfd, LISTENQ);

    client[0].fd = listenfd;
    client[0].events = POLLRDNORM;
    for (i = 1; i<FOPEN_MAX; i++)
        client[i].fd = -1;        /* -1 indicates available entry */
    maxi = 0;                    /* max index into client[] array */

    for (;;) {
        nready = Poll(client, maxi+1, INFTIM);

        if (client[0].revents & POLLRDNORM) {    /* new client connection */
            clilen = sizeof(cliaddr);
            connfd = Accept(listenfd, (SA*) & cliaddr, &clilen);
            //printf("new client: %s\n", Sock_ntop((SA *) &cliaddr, clilen));

            for (i = 1; i<FOPEN_MAX; i++)
                if (client[i].fd<0) {
                    client[i].fd = connfd;    /* save descriptor */
                    break;
                }
            if (i==FOPEN_MAX)
                err_quit("too many clients");

            client[i].events = POLLRDNORM;
            if (i>maxi)
                maxi = i;                /* max index in client[] array */

            if (--nready<=0)
                continue;                /* no more readable descriptors */
        }

        for (i = 1; i<=maxi; i++) {    /* check all clients for data */
            if ((sockfd = client[i].fd)<0)
                continue;
            if (client[i].revents & (POLLRDNORM | POLLERR)) {
                if ((n = read(sockfd, buf, MAXLINE))<0) {
                    if (errno==ECONNRESET) {
                        /*4connection reset by client */
#ifdef    NOTDEF
                        printf("client[%d] aborted connection\n", i);
#endif
                        Close(sockfd);
                        client[i].fd = -1;
                    }
                    else
                        err_sys("read error");
                }
                else if (n==0) {
                    /*4connection closed by client */
#ifdef    NOTDEF
                    printf("client[%d] closed connection\n", i);
#endif
                    Close(sockfd);
                    client[i].fd = -1;
                }
                else
                    Writen(sockfd, buf, n);

                if (--nready<=0)
                    break;                /* no more readable descriptors */
            }
        }
    }
}

