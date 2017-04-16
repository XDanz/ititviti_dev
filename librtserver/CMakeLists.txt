set(libfoo2_SRCS
        EchoServer.h
        EchoServer.cpp
        Wraplib.cpp
)

# Declare the library
add_library(libfoo2 STATIC
    ${libfoo2_SRCS}
)


target_link_libraries(libfoo2
        libbar
        pthread
        )
# Specify here the include directories exported
# by this library
target_include_directories(libfoo2 PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
