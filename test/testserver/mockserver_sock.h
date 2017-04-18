#include <IServerSocket.h>
#include "gmock/gmock.h"

class MockIServerSocket : public IServerSocket {
public:
    MOCK_METHOD2(Bind,
            void(const struct sockaddr *sa, socklen_t salen));
    MOCK_METHOD1(Listen,
            void(int backlog));
    MOCK_METHOD2(Accept,
            int(struct sockaddr *sa, socklen_t *salenptr));
};



