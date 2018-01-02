#include "testencoder.h"
#include "../../libsockutil/Encoder.h"

EncoderTest::EncoderTest() {

}

EncoderTest::~EncoderTest() {};

void EncoderTest::SetUp() {};

void EncoderTest::TearDown() {};

TEST_F(EncoderTest, encodeIntBigEndian)
{
    Encoder encoder;
    uint64_t val = 10;
    uint8_t dest[sizeof(uint64_t)];
    ASSERT_EQ(8, encoder.encodeIntBigEndian(dest, val, 0, sizeof(uint64_t)));
    auto i=0;
    // the first 7 bytes should be zero
    for(;i<7;i++)
    ASSERT_EQ(0L, dest[i]);

    ASSERT_EQ(10L, dest[i]);

}

TEST_F(EncoderTest, encodeIntBigEndian_with_2_bytes)
{
    Encoder encoder;
    uint64_t val = 0xffff;
    uint8_t dest[sizeof(uint64_t)];
    ASSERT_EQ(8, encoder.encodeIntBigEndian(dest, val, 0, sizeof(uint64_t)));
    // the first 6 bytes should be zero
    auto i=0;
    for(;i<6;i++)
        ASSERT_EQ(0L, dest[i]);

    ASSERT_EQ(0xff, dest[i]);
    ASSERT_EQ(0xff, dest[++i]);

}

