//
// Created by danter on 2016-08-02.
//
#include <gtest/gtest.h>
#include "Decoder.h"

TEST(Simple, tree_is_root)
{
    ClientSocketMock mock;
    Decoder decoder;
    uint64_t val = 10;
    uint8_t be[sizeof(uint64_t)];
    //ASSERT_EQ(8, decoder.decodeIntBigEndian(be, val, 0, sizeof(uint64_t)));

}