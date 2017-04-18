file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testclient ${SRCS} mockclient_sock.h)

TARGET_LINK_LIBRARIES(testclient
    libclient
    libsockutil
    libgtest
    libgmock
)

add_test(NAME testclient
         COMMAND testclient)
