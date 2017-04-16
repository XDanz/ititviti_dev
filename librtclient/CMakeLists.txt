set(libfoo_SRCS
    foo.h
    foo.cpp
    ibar.h
        RTClient.cpp
        RTClient.h
)
find_package(Threads REQUIRED)
# Declare the library
add_library(libfoo STATIC
    ${libfoo_SRCS}
)

target_link_libraries(libfoo
        libbar
        pthread
        )

# Specify here the include directories exported
# by this library
target_include_directories(libfoo PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
