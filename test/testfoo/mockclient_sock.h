#include "gmock/gmock.h"
#include "IClientSocket.h"

class Mockclient_sock: public IClientSocket
{
public:
    MOCK_METHOD2(connectSocket, void(sockaddr* sockaddr, socklen_t socklen));
    MOCK_METHOD2(writeToSocket, void(void* ptr, size_t nbytes));
    MOCK_METHOD2(setAddr, void(const std::string host, void* buf));
    MOCK_METHOD2(readFromSocket, ssize_t(void* ptr, size_t nbytes));
};


