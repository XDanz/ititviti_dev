file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testserver ${SRCS} testserver.h mockserver_sock.h)

TARGET_LINK_LIBRARIES(testserver
    libserver
    libsockutil
    libgtest
    libgmock
)

add_test(NAME testserver
         COMMAND testserver)
