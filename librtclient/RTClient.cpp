/**
 * @file   RTClient.h
 * @Author Daniel Terranova (daniel.terranova@gmail.com)
 * @date   April, 2017
 * @brief  File contains declaration of the TCP Client which calculate RTT of a message.
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
        clientSocket.readFromSocket(in, sizeof(uint64_t));

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        uint64_t val = decoder.decodeIntBigEndian(in, 0, sizeof(uint64_t));
        std::unordered_map<uint64_t,std::chrono::steady_clock::time_point>::iterator iterator;
        /** lock the mutex here before accessing the map **/
        map_guard_mutex.lock();
        iterator = messages.find(val);
        std::cout << "get " << val << std::endl;
        if (iterator != messages.end())
        {
            double rtt = millis_diff(end, iterator->second);
            avg += rtt;
            std::cout << "RT = " << rtt
                      << " millis, RT rate: " << (sizeof(uint64_t)*1000)/(rtt) << " Bps" << std::endl;

            size_t before = messages.size();
            messages.erase(iterator);
            if (before > 0) {
                if ((before-1)!=messages.size())
                {
                    char buf[1025];
                    snprintf(buf, 1025, "Error could not remove message %ld in map", val);
                    throw std::runtime_error(buf);
                }
            }

        } else {
            char buf[1025];
            snprintf(buf, 1025, "Error could not find message %ld in map", val);
            throw std::runtime_error(buf);
        }
        map_guard_mutex.unlock();
    }

    producer.join();
    clientSocket.Close();
    std::cout << "Avg: " << avg/double(cnt) << " millis" << std::endl;
}

double RTClient::millis_diff(std::chrono::steady_clock::time_point end, std::chrono::steady_clock::time_point start)
{
    double delta = std::chrono::duration_cast<std::chrono::nanoseconds> (end - start).count()/double(1000000);
    return delta;
}

void RTClient::message_produce()
{   uint8_t out[sizeof(uint64_t)];
    Encoder encoder;

    for (uint64_t i = 0; i < cnt; i++)
    {
        encoder.encodeIntBigEndian(out, i, 0, sizeof(uint64_t));
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        map_guard_mutex.lock();
        messages.insert(std::pair<uint64_t, std::chrono::steady_clock::time_point>{i, begin});
        map_guard_mutex.unlock();
        std::cout << "put " << i << std::endl;
        clientSocket.writeToSocket(out, sizeof(uint64_t));
    }
}