#include <Encoder.h>
#include "testencoder.h"

EncoderTest::EncoderTest() {

}

EncoderTest::~EncoderTest() {};

void EncoderTest::SetUp() {};

void EncoderTest::TearDown() {};

TEST_F(EncoderTest, encodeIntBigEndian)
{
    Encoder encoder;
    uint64_t val = 10;
    uint8_t be[sizeof(uint64_t)];
    ASSERT_EQ(8, encoder.encodeIntBigEndian(be, val, 0, sizeof(uint64_t)));
    ASSERT_EQ(uint8_t(10), be[7]);

}

