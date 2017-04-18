#include <RTClient.h>
#include "foo.h"
#include "testfoo.h"

using ::testing::Return;
using ::testing::_;
using ::testing::AtLeast;

FooTest::FooTest() {
    // Have qux return true by default
    //ON_CALL(m_bar,qux()).WillByDefault(Return(true));
    // Have norf return false by default
    //ON_CALL(m_bar,norf()).WillByDefault(Return(false));
    //ON_CALL(sock, setAddr(_,_)).WillByDefault(Return());
    //ON_CALL(sock, connectSocket(_,_)).WillByDefault(Return());
}

FooTest::~FooTest() {};

void FooTest::SetUp() {};

void FooTest::TearDown() {};

TEST_F(FooTest, clientTest) {
    EXPECT_CALL(sock, setAddr(std::string("127.0.0.1"),_)).Times(AtLeast(1));
    EXPECT_CALL(sock, connectSocket(_,_)).Times(AtLeast(1));
    uint16_t port = uint16_t(10);
    RTClient rtClient (sock, "127.0.0.1", port, 5);
}

