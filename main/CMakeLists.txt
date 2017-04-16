set(MainClient_SRCS
    ClientMain.cpp
)

set(MainServer_SRCS
        ServerMain.cpp
        )

add_executable(myAppClient
    ${MainClient_SRCS}
)

add_executable(myAppServer
    ${MainServer_SRCS}
)

# Specify here the libraries this program depends on
target_link_libraries(myAppClient
    libfoo
    libbar
)

target_link_libraries(myAppServer
        libfoo2
        libbar
        )


install(TARGETS myAppClient DESTINATION bin)
install(TARGETS myAppServer DESTINATION bin)
