cmake_minimum_required(VERSION 3.3)
file(GLOB *.cpp)

add_executable(test_decoder Decoder_test.cpp ../../libbar/Decoder.cpp Decoder_test_main.cpp)
include_directories(../../include)
target_link_libraries(test_decoder
        libgtest
        libgmock
        )

install(TARGETS test_decoder DESTINATION bin)