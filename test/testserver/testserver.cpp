#include "testserver.h"
#include <IServerSocket.h>
#include <EchoServer.h>

using ::testing::Return;
using ::testing::_;
using ::testing::AtLeast;

ServerTest::ServerTest() {
}

ServerTest::~ServerTest() {};

void ServerTest::SetUp() {};

void ServerTest::TearDown() {};

TEST_F(ServerTest, serverTest) {
    EXPECT_CALL(sock, Bind(_,_)).Times(AtLeast(1));
    EXPECT_CALL(sock, Listen(_)).Times(AtLeast(1));
//    EXPECT_CALL(sock, (_,_)).Times(AtLeast(5));
//    EXPECT_CALL(sock, writeToSocket(_,_)).Times(AtLeast(5));
    EXPECT_CALL(sock, )
    uint16_t port = uint16_t(10);
    EchoServer rtServer (sock, "127.0.0.1", port);
    rtServer.start();
}

