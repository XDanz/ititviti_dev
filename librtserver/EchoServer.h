/**
 * @file   EchoServer.h
 * @Author Daniel Terranova (daniel.terranova@gmail.com)
 * @date   April, 2017
 * @brief  File contains declaration of the TCP Echo server. The only purpose of this
 * class is to bind,listen and echo back request made from clients.
 *
 * The server is a single process that uses I/O multiplexing with poll() system call.
 * The reason to use poll() instead of multiple threads is to use one thread
 * that handle multiple client sockets (including the listening socket) and it suffice
 * for this solution.
 */

#ifndef ITIVITI_DEV_ECHOSERVER_H
#define ITIVITI_DEV_ECHOSERVER_H

#include <sys/socket.h>
#include <string>
#include <IServerSocket.h>

class EchoServer {

public:
    EchoServer(IServerSocket& serverSocket, const std::string& host, uint16_t port):
            serverSocket(serverSocket), serverHost(host), serverPort(port)
    {

        serverSocket.createSocket();

        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        Inet_pton(AF_INET, serverHost.c_str(), &servaddr.sin_addr.s_addr);
        servaddr.sin_port = htons(serverPort);

        serverSocket.Bind((sockaddr *) & servaddr, sizeof(servaddr));

        serverSocket.Listen(LISTENQ);

        client[0].fd = serverSocket.getSockfd();
        client[0].events = POLLRDNORM; // register that we are interested in read event

        /** initialize all the entries in client[] array
         * -1 indicates available entry no client fd stored
         **/
        for (i = 1; i< FOPEN_MAX; i++)
            client[i].fd = -1;        /* -1 indicates available entry */
        maxi = 0;                    /* max index into client[] array */

    };
    void start();
protected:
    const uint16_t serverPort;
    const std::string& serverHost;
    const int  LISTENQ = 1024;
    const int  INFTIM  = (-1);
private:
    void Inet_pton(int family, const char *strptr, void *addrptr);
    IServerSocket& serverSocket;
    int i, maxi;
    const size_t MAXLINE = 4096;	/* max text line length */
    char buf[4096];
    socklen_t clilen;
    struct pollfd client[FOPEN_MAX];
    struct sockaddr_in cliaddr, servaddr;

    /**
     * @Brief After a call to Poll the listening file descriptor is checked for readiness
     * which means that system call accept can be performed.
     *
     * @return true/false weather the listening file descriptor is ready for I/O
     */
    bool isAcceptable() const {
        return bool(client[0].revents & POLLRDNORM);
    }

    /**
     * @Brief After a call to Poll the client fd at position iis checked for readiness
     * which means that system call read can be performed without blocking.
     *
     * @return true/false weather the descriptor at position i is ready for I/O
     */
    bool isReadable(int i) const {
        return bool(client[i].revents & (POLLRDNORM | POLLERR));
    }

    /**
     * @Brief connection reset by client at position i when read() returns < 0
     *
     */
    void clientAborted(int i)
    {   printf("client[%d] aborted connection\n", i);
        removeClient(i);
    }

    /**
     * @Brief connection reset by client at position i when read() returns = 0
     * FIN or EOF has been received
     */
    void clientClosed(int i)
    {   printf("client[%d] closed connection\n", i);
        removeClient(i);
    }

    /**
     * @Brief When client fd no longer needed remove and close the fd at position i
     *
     */
    void removeClient(int i)
    {   ErrorUtil::Close(client[i].fd);
        client[i].fd = -1;
    }

    /**
     * @Brief Stores or save a new client fd at some available position in the client[] array
     * increase the high water mark maxi if needed.
     *
     * Set the interested event to read event the application is interested in
     * for the file descriptor connfd.
     *
     * @param connfd The connfd to be stored as a connected client
     */
    void store_clientfd(int connfd)
    {
        for (i = 1; i < FOPEN_MAX; i++)
        {
            if (client[i].fd < 0)
            {
                client[i].fd = connfd;
                break;
            }
        }

        if (i == FOPEN_MAX)
            throw std::runtime_error(ErrorUtil::err_sys("too many clients"));

        client[i].events = POLLRDNORM;
        if (i > maxi)
            maxi = i;
    }
};

#endif //ITIVITI_DEV_ECHOSERVER_H
