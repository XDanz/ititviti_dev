set(libbar_SRCS
        ErrorUtil.h
        ErrorUtil.cpp
        IClientSocket.h
        IServerSocket.h
        Decoder.h
        Decoder.cpp
        Encoder.h
        Encoder.cpp
        SocketUtil.h
        GenericSocket.h
        ClientSocketImpl.h
        ServerSocketImpl.h
        )

# Declare the library
add_library(libsockutil STATIC
    ${libbar_SRCS}
)

# Specify here the include directories exported
# by this library
target_include_directories(libsockutil PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
