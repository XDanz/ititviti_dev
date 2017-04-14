cmake_minimum_required(VERSION 3.3)
file(GLOB *.cpp)

add_executable(test_encoder Encoder_test.cpp ../../src/Encoder.cpp Encoder_test_main.cpp Encoder_test_main.cpp ../encoder_test/ClientSocketMock.cpp)
include_directories(../../include)
target_link_libraries(test_encoder
        libgtest
        libgmock
        )

install(TARGETS test_encoder DESTINATION bin)