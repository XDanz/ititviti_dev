cmake_minimum_required(VERSION 3.3)
project(itiviti_dev)

find_package(Threads REQUIRED)

set(PROJECT_NAME_STR itiviti_dev)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#-------------------
# set common include folder for module
#-------------------
set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/ext)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

add_subdirectory(src)
add_subdirectory(gtest)
#
##-------------------
## Test
##-------------------
#add_definitions(${MSVC_COMPILER_DEFS})
#enable_testing()
#set(PROJECT_TEST_NAME ${PROJECT_NAME_STR}_test)
#include_directories(${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})
#
#file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)
#file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
#add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES} ${SRC_FILES} test/tree_test.cpp)
#MESSAGE( STATUS "(PROJECT_TEST_NAME):" ${PROJECT_TEST_NAME})
#MESSAGE( STATUS "(TEST_SRC_FILES):" ${TEST_SRC_FILES} )
#add_dependencies(${PROJECT_TEST_NAME} googletest)
#
#
#if(NOT WIN32 OR MINGW)
#    target_link_libraries(${PROJECT_TEST_NAME}
#            ${GTEST_LIBS_DIR}/libgtest.a
#            ${GTEST_LIBS_DIR}/libgtest_main.a
#            )
#else()
#    target_link_libraries(${PROJECT_TEST_NAME}
#            debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
#            optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
#            )
#    target_link_libraries(${PROJECT_TEST_NAME}
#            debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
#            optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
#            )
#endif()
#
#target_link_libraries(${PROJECT_TEST_NAME} ${CMAKE_THREAD_LIBS_INIT})
#
#add_test(test1 ${PROJECT_TEST_NAME})