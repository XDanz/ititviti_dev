cmake_minimum_required(VERSION 3.3)
project(itiviti_dev)

find_package(Threads REQUIRED)

enable_testing()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

##-------------------
## set common include folder for module
##-------------------
#set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
#set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/ext)
#
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

add_subdirectory(main)
add_subdirectory(test)
add_subdirectory(librtclient)
add_subdirectory(librtserver)
add_subdirectory(libbar)
