#include "testserver.h"
#include "../../librtclient/RTClient.h"

using ::testing::Return;
using ::testing::_;
using ::testing::AtLeast;
using ::testing::Exactly;

RTClientTest::RTClientTest() {
}

RTClientTest::~RTClientTest() {};

void RTClientTest::SetUp() {
    sock.DelegateToFake();
};

void RTClientTest::TearDown() {};

TEST_F(RTClientTest, clientTest) {
    EXPECT_CALL(sock, setAddr(std::string("127.0.0.1"),_)).Times(Exactly(1));
    EXPECT_CALL(sock, connectSocket(_,_)).Times(Exactly(1));
    EXPECT_CALL(sock, readFromSocket(_,_)).Times(Exactly(5));
    EXPECT_CALL(sock, writeToSocket(_,_)).Times(Exactly(5));
    auto port = uint16_t(10);
    RTClient rtClient (sock, "127.0.0.1", port, 5);
    rtClient.start();
}

