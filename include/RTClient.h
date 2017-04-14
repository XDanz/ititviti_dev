/**
 * @file   RTClient.h
 * @Author Daniel Terranova (daniel.terranova@gmail.com)
 * @date   April, 2017
 * @brief  File contains declaration of the TCP Client which calculate RTT of a messages.
 *
 * RT Client (or Round trip Client) sends messages (uint64_t) to the server
 * and calculate the Round trip time for the messages. A message is stored as a key
 * in a std::map with the value as std::chrono::steady_clock::time_point. Just before it is written to the underlying
 * socket the time_point is created and adds the key value pair association to the std::map.
 *
 * The RTClient uses the calling thread of the member function start() to read data from the socket. The RTClient
 * starts an additional thread in start() (which runs mesagess_produce()) that writes n messages to the same socket.
 *
 * When a message is receive a new std::chrono::steady_clock::time_point is created and the message is
 * retrieved from std::map. The value in the pair is used to calculate the round trip time
 * which is displayed in milliseconds.
 *
 * The calculated RTT is not as accurate as it could be because the bytes to transport
 * over the network layer is not sent immediately, instead it is transported to the
 * sending tcp buffer, before sending it over the network layer to the receiving tcp buffer on the server side.
 *
 * For this implementation the time that the bytes is in the
 * sending/receiving tcp buffer on client and server side is included in the round trip calculation.
 *
 *
 */
#ifndef ITIVITI_DEV_RTCLIENT_H
#define ITIVITI_DEV_RTCLIENT_H

#include <sys/socket.h>
#include <string>
#include <map>
#include "ErrorUtil.h"
#include "IClientSocket.h"
#include <chrono>
#include <string.h>
#include <arpa/inet.h>

class RTClient {
public:
    /**
     * @Brief Constructor to initiate RTClient
     *
     * The constructor creates a socket and connects the given socket to the IPv4 address and tcp port
     * to the server.
     *
     * @param host string containing an IPv4 network address in dotted-decimal
     * format to connect to
     *
     * @param port TCP port corresponding the listening host to which the client connect to
     *
     * @param cnt Number of messages to produce
     */
    RTClient(IClientSocket& sockApi, const std::string& host, uint16_t port, uint64_t cnt):
            sockApi(sockApi), host(host), port(port), cnt(cnt)
    {   struct sockaddr_in	servaddr;

        sockApi.createSocket();
        bzero(&servaddr, sizeof(servaddr));

        servaddr.sin_family = AF_INET;
        servaddr.sin_port   = htons(port);

        sockApi.setAddr(host,&servaddr.sin_addr);
        sockApi.connectSocket((sockaddr*) &servaddr, sizeof(servaddr));
    };

    /**
     * @Brief member function to initiate the sending/listening of messages
     *
     * The member function start a thread that writes messages to the socket and
     * the calling thread reads messages from the socket.
     *
     * Calculate and display the round trip time in milliseconds for each message,
     * average round trip time for all messages in milliseconds and throughput of messages send to
     * the socket in Bps (Bytes per seconds).
     */
    void start();
private:
    /**
     * @Brief The member function to run by the starting thread which writes n messages
     * to the socket
     */
    void message_produce();

    /**
     * @Brief host string containing an IPv4 network address in dotted-decimal format
     */
    const std::string& host;

    /**
     * @Brief TCP port to connect to
     */
    const uint16_t port;

    /**
     * @Brief Number of messages to write to the socket
     */
    uint64_t cnt;

    /**
     * @Brief map that contains mapping between the message and the time_point before it is written
     * to the socket
     *
     * Each message is associated with a time_point before written to the socket this is used to calculate
     * the round trip time for each message.
     */
    std::map<uint64_t,std::chrono::steady_clock::time_point> messages;

    /**
     * @Brief SockApi is a wrapper class that wraps socket system calls.
     *
     */
    IClientSocket& sockApi;

    /**
     * @name    millis_diff()
     * @brief   An utility member function to be able to calculate difference between two time_point
     *
     * This API provides utility member function to calculate difference between two time_point displayed
     * in units of milliseconds
     *
     * @param [in] end The end time_point
     * @param [in] start The start time_point
     *
     * @retval Delta difference (end-start) in milliseconds units
     *
     */
    double millis_diff(std::chrono::steady_clock::time_point end, std::chrono::steady_clock::time_point start);

    /**
     * @Brief The average multiplied by the cnt to calculate the average round trip time of all messages
     *
     */
    double avg = 0;

    /**
     * @Brief The elapsed time of all the written cnt messages. This is used to calculate throughput
     *
     */
    double elapsed = 0;
};
#endif //ITIVITI_DEV_RTCLIENT_H
