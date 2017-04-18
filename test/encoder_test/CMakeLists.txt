file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testencoder ${SRCS})

TARGET_LINK_LIBRARIES(testencoder
    libsockutil
    libgtest
    libgmock
)

add_test(NAME testencoder
         COMMAND testencoder)
