#include "testserver.h"
#include "../../librtclient/RTClient.h"

using ::testing::Return;
using ::testing::_;
using ::testing::AtLeast;

RTClientTest::RTClientTest() {
}

RTClientTest::~RTClientTest() {};

void RTClientTest::SetUp() {};

void RTClientTest::TearDown() {};

TEST_F(RTClientTest, clientTest) {
    EXPECT_CALL(sock, setAddr(std::string("127.0.0.1"),_)).Times(AtLeast(1));
    EXPECT_CALL(sock, connectSocket(_,_)).Times(AtLeast(1));
    EXPECT_CALL(sock, readFromSocket(_,_)).Times(AtLeast(5));
    EXPECT_CALL(sock, writeToSocket(_,_)).Times(AtLeast(5));
    uint16_t port = uint16_t(10);
    RTClient rtClient (sock, "127.0.0.1", port, 5);
    rtClient.start();
}

