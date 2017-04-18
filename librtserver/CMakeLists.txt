set(libserver_SRCS
        EchoServer.h
        EchoServer.cpp
        Inet_pton.cpp
)

# Declare the library
add_library(libserver STATIC
    ${libserver_SRCS}
)

target_link_libraries(libserver
        libsockutil
        pthread
        )
# Specify here the include directories exported
# by this library
target_include_directories(libserver PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
