//
// Created by danter on 2017-04-10.
//
#include <string>
#include <iostream>
#include <EchoServer.h>
#include <ServerSocketImpl.h>

int
main(int argc, char **argv)
{
    int c;
    std::string host;
    ServerSocketImpl serverSocket{};
    char *end = nullptr;
    auto port = static_cast<uint16_t>(-1);

    /* Parse command line */
    while ((c = getopt(argc, argv, "a:p:")) != EOF) {
        switch (c) {
        case 'a':
            host = optarg;
            break;
        case 'p': {
            auto cand = std::strtoul(optarg, &end, 10);
            if (optarg == end) {
                std::cerr << "cannot convert: " << optarg << " to uintt_16" << std::endl;
                exit(1);
            }
            port = uint16_t();

            break;
        }
        default:
            printf("huh?\n");
            exit(1);
        }
    }
    if (port == static_cast<uint16_t>(-1)) {
        std::cerr << "-p is mandatory!" << std::endl;
        exit(1);
    }

    argc -= optind;
    argv += optind;
    try {
        EchoServer server {serverSocket, host, port};
        server.start();
    } catch (std::runtime_error &exception) {
        std::cerr << exception.what() << std::endl;
    }

}
