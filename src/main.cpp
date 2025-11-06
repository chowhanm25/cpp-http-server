#include "http_server.h"
#include <iostream>
#include <csignal>
#include <memory>

std::unique_ptr<HttpServer> server;

void signalHandler(int signum)
{
    std::cout << "\nInterrupt signal (" << signum << ") received.\n";
    if (server)
    {
        server->stop();
    }
    exit(signum);
}

int main(int argc, char *argv[])
{
    int port = 8080;
    int threads = 4;

    if (argc > 1)
    {
        port = std::atoi(argv[1]);
    }
    if (argc > 2)
    {
        threads = std::atoi(argv[2]);
    }

    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    try
    {
        server = std::make_unique<HttpServer>(port, threads);
        std::cout << "Starting HTTP Server on port " << port
                  << " with " << threads << " threads..." << std::endl;
        server->start();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}