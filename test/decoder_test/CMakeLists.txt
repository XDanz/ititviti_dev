file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testdecoder ${SRCS})

TARGET_LINK_LIBRARIES(testdecoder
        libsockutil
        libgtest
        libgmock
        )

add_test(NAME testdecoder
        COMMAND testdecoder)