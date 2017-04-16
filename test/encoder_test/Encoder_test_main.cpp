//
// Created by danter on 2017-04-12.
//

#include <gmock/gmock.h>
#include "gtest/gtest.h"

int main(int argc, char **argv)
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}