//
// Created by danter on 2017-04-10.
//

#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <chrono>
#include <iostream>
#include <iomanip>
#include "RTClient.h"
#include "Encoder.h"
#include "Decoder.h"
#include <thread>

void RTClient::start()
{
    std::thread producer([this] { this->producer_thread(); });

    uint8_t in[sizeof(uint64_t)];
    Decoder decoder;
    for (uint64_t i = 0; i < cnt; i++) {
        Readn(sockfd, in, sizeof(uint64_t));

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        uint64_t val = decoder.DecodeIntBigEndian(in,0, sizeof(uint64_t));
        std::map<uint64_t,std::chrono::steady_clock::time_point>::iterator iterator;
        iterator = messages.find(val);
        if (iterator != messages.end()) {
            double rtt = millis_diff(end, iterator->second);
            avg += rtt;
            std::cout << "RT = " << millis_diff(end, iterator->second)
                      << " millis" << std::endl;
        }
    }

    producer.join();
    std::cout << "Avg: " << avg/double(cnt) << " millis" << std::endl;
    std::cout << "Throughput: " << (cnt*sizeof(uint64_t)*1000)/(elapsed) << " Bps" << std::endl;
}

double RTClient::millis_diff(std::chrono::steady_clock::time_point end, std::chrono::steady_clock::time_point start) {
    double delta = std::chrono::duration_cast<std::chrono::nanoseconds> (end - start).count()/double(1000000);
    return delta;
}

void * RTClient::producer_thread()
{   uint8_t out[sizeof(uint64_t)];
    Encoder encoder;

    std::chrono::steady_clock::time_point start_run = std::chrono::steady_clock::now();
    for (uint64_t i = 0; i < cnt; i++)
    {
        encoder.EncodeIntBigEndian(out, i, 0 , sizeof(uint64_t));
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        messages.insert(std::pair<uint64_t, std::chrono::steady_clock::time_point>{i, begin});
        Writen(sockfd, out, sizeof(uint64_t));
    }
    std::chrono::steady_clock::time_point end_run = std::chrono::steady_clock::now();
    elapsed = millis_diff(end_run, start_run);

}