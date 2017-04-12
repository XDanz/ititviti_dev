/**
 * @file   RTClient.h
 * @Author Daniel Terranova (daniel.terranova@gmail.com)
 * @date   April, 2017
 * @brief  File contains declaration of the TCP Client which calculate RTT of a message.
 *
 * RT Client or Round Trip Client send a message as a unsigned integer to the server
 * and calculate th Round Trip time for a message. The unsigned integer is stored
 * in a map together with a starting time before it is written to the underlying
 * TCP Buffer.
 *
 * The calculated RTT is not as accurate as it could be because the bytes to transport
 * over the network layer is not sent immediately instead it is transported to the
 * TCP buffer in kernel space. For this implementation the time that the bytes is in the
 * TCP buffer is included in RTT and also the time it spends in TCP Buffer on the
 * receiving end.
 *
 * The RTClient uses the calling thread to receive bytes from the socket while it
 * starts additional thread that produces messages.
 *
 */
#ifndef ITIVITI_DEV_RTCLIENT_H
#define ITIVITI_DEV_RTCLIENT_H

#include <sys/socket.h>
#include <string>
#include <map>
#include "RTPeer.h"
#include <chrono>
#include <string.h>
#include <arpa/inet.h>

class RTClient: public RTPeer {
public:
    /**
     * Constructor to initiate RTClient
     *
     * @param host string containing an IPv4 network address in dotted-decimal
     * format to connect to
     * @param port TCP port corresponding the listening host to which the client connect to
     * @param cnt Number of messages to produce
     */
    RTClient(const std::string& host, int port, int cnt): host(host),
                                                          port(port), cnt(cnt) {
        struct sockaddr_in	servaddr;

        if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
            err_sys("socket error");

        bzero(&servaddr, sizeof(servaddr));

        servaddr.sin_family = AF_INET;
        servaddr.sin_port   = htons(port);
        if (inet_pton(AF_INET, host.c_str(), &servaddr.sin_addr) <= 0)
            err_quit("inet_pton error for %s", host.c_str());

        if (connect(sockfd, (sockaddr *) &servaddr, sizeof(servaddr)) < 0)
            err_sys("connect error");

    };
    /**!
     * Start producing messages to the listening service
      * Calculate and display the round	trip time in milliseconds for each message
      */
    void start();
private:
    // The method to run by starting thread
    void producer_thread();

    // host string containing an IPv4 network address in dotted-decimal
    const std::string& host;

    // TCP port to connect to
    int port;

    // Number of messages to send
    uint64_t cnt;

    // Each message is associated with a start clock to be able to count
    // the round trip time, each message is identified by message count which increases monotonically.
    std::map<uint64_t,std::chrono::steady_clock::time_point> messages;

 /*!
  * @name    millis_diff()
  * @brief   An utility member function to be able to calculate diff between two points in time
  *
  * This API provides utility member function to calculate diff between two points in time
  *
  * @param [in] end The end time point
  * @param [in] start The start time point
  *
  * @retval Delta diff (=end-start) in milliseconds with nano precision
  *
  */
    double millis_diff(std::chrono::steady_clock::time_point end, std::chrono::steady_clock::time_point start);
    double avg = 0; // The average multiplied by the cnt to calculate the average
    double elapsed = 0; // The elapsed time of all the written cnt messages. This is used to calculate throughput
    int sockfd;  // socket file descriptor
};
#endif //ITIVITI_DEV_RTCLIENT_H
