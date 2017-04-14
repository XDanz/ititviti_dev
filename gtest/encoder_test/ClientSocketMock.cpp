//
// Created by danter on 2017-04-14.
//
#include "gmock/gmock.h"
#include "IClientSocket.h"

class MockIClientSocket : public IClientSocket {
public:
    MOCK_METHOD2(connectSocket,
            void(sockaddr* sockaddr, socklen_t socklen));
    MOCK_METHOD2(writeToSocket,
            const void(void* ptr, size_t nbytes));
    MOCK_METHOD2(setAddr,
            void(const std::string host, void* buf));
    MOCK_METHOD2(readFromSocket,
            ssize_t(void* ptr, size_t nbytes));
    MOCK_METHOD0(tt,
            int());
    MOCK_METHOD1(tv,
            int(int x));
};
