/**
 * @file   RTClient.h
 * @Author Daniel Terranova (daniel.terranova@gmail.com)
 * @date   April, 2017
 * @brief  File contains declaration of the TCP Client which calculate RTT of a message.
 *
 * Detailed description of file.
 *
 */
#include <netinet/in.h>
#include <chrono>
#include <iostream>
#include <iomanip>
#include "RTClient.h"
#include <Decoder.h>
#include <Encoder.h>
#include <thread>

void RTClient::start()
{   std::thread producer([this] { this->message_produce(); });

    uint8_t in[sizeof(uint64_t)];
    Decoder decoder;
    for (uint64_t i = 0; i < cnt; i++)
    {
        sockApi.readFromSocket(in, sizeof(uint64_t));

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        uint64_t val = decoder.decodeIntBigEndian(in, 0, sizeof(uint64_t));
        std::map<uint64_t,std::chrono::steady_clock::time_point>::iterator iterator;
        iterator = messages.find(val);
        if (iterator != messages.end())
        {
            double rtt = millis_diff(end, iterator->second);
            avg += rtt;
            std::cout << "RT = " << rtt
                      << " millis" << std::endl;

            messages.erase(iterator);
        }
    }

    producer.join();
    std::cout << "Avg: " << avg/double(cnt) << " millis" << std::endl;
    std::cout << "Throughput: " << (cnt*sizeof(uint64_t)*1000)/(elapsed) << " Bps" << std::endl;
}

double RTClient::millis_diff(std::chrono::steady_clock::time_point end, std::chrono::steady_clock::time_point start)
{
    double delta = std::chrono::duration_cast<std::chrono::nanoseconds> (end - start).count()/double(1000000);
    return delta;
}

void RTClient::message_produce()
{   uint8_t out[sizeof(uint64_t)];
    Encoder encoder;

    std::chrono::steady_clock::time_point start_run = std::chrono::steady_clock::now();
    for (uint64_t i = 0; i < cnt; i++)
    {
        encoder.encodeIntBigEndian(out, i, 0, sizeof(uint64_t));
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        messages.insert(std::pair<uint64_t, std::chrono::steady_clock::time_point>{i, begin});
        sockApi.writeToSocket(out, sizeof(uint64_t));
    }
    std::chrono::steady_clock::time_point end_run = std::chrono::steady_clock::now();
    elapsed = millis_diff(end_run, start_run);
}