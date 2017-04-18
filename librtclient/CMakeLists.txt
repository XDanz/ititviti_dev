set(libclient_SRCS
        RTClient.cpp
        RTClient.h
)
find_package(Threads REQUIRED)
# Declare the library
add_library(libclient STATIC
    ${libclient_SRCS}
)

target_link_libraries(libclient
        libsockutil
        pthread
        )

# Specify here the include directories exported
# by this library
target_include_directories(libclient PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
