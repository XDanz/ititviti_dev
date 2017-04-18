file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testencoder ${SRCS})

TARGET_LINK_LIBRARIES(testencoder
    libfoo
    libfoo2
    libgtest
    libgmock
)

add_test(NAME testencoder
         COMMAND testencoder)
