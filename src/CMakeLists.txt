cmake_minimum_required(VERSION 3.3)
project(src)

find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

#-------------------
# set common include folder for module
#-------------------

include_directories(../include)
add_executable(server_start Main.cpp EchoServer.cpp Writen.cpp Wraplib.cpp RTPeer.cpp)
add_executable(client_start ClientMain.cpp RTClient.cpp RTPeer.cpp Encoder.cpp Decoder.cpp Readn.cpp Writen.cpp)

