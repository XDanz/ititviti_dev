set(libbar_SRCS
        ErrorUtil.h
        ErrorUtil.cpp
        IClientSocket.h
        IServerSocket.h
        Decoder.h
        Decoder.cpp
        Encoder.h
        Encoder.cpp
        IOUtil.h
        ISocket.h
        ClientSocketImpl.h
        )

# Declare the library
add_library(libbar STATIC
    ${libbar_SRCS}
)

#target_link_libraries(libbar
#    libfoo libfoo2
#)

# Specify here the include directories exported
# by this library
target_include_directories(libbar PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
