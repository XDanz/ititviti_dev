find_package(Threads REQUIRED)
set(MainClient_SRCS
        ClientMain.cpp
        )

set(MainServer_SRCS
        ServerMain.cpp
        )

add_executable(client_start
        ${MainClient_SRCS}
        )

add_executable(server_start
        ${MainServer_SRCS}
        )

# Specify here the libraries this program depends on
target_link_libraries(client_start
        libclient
        libsockutil
        pthread
        )

target_link_libraries(server_start
        libserver
        libsockutil
        pthread
        )


install(TARGETS client_start DESTINATION bin)
install(TARGETS server_start DESTINATION bin)
