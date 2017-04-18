//
// Created by danter on 2016-08-02.
//
#include <gtest/gtest.h>
#include "../../libsockutil/Decoder.h"

TEST(DecoderTest, decoder_test)
{
    Decoder decoder;
    uint8_t be[sizeof(uint64_t)];
    be[0] = uint8_t(0);
    be[1] = uint8_t(0);
    be[2] = uint8_t(0);
    be[3] = uint8_t(0);
    be[4] = uint8_t(0);
    be[5] = uint8_t(0);
    be[6] = uint8_t(0);
    be[7] = uint8_t(10);

    ASSERT_EQ(uint64_t(10), decoder.decodeIntBigEndian(be, 0, sizeof(uint64_t)));

}