#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <string>
#include <memory>
#include "thread_pool.h"

class HttpServer
{
public:
    HttpServer(int port, int thread_count = 4);
    ~HttpServer();

    void start();
    void stop();

private:
    void handleClient(int client_socket);
    std::string parseRequest(const std::string &request);
    std::string buildResponse(int status_code, const std::string &content_type,
                              const std::string &body);
    std::string getContentType(const std::string &path);
    std::string readFile(const std::string &path);

    int port_;
    int server_socket_;
    bool running_;
    std::unique_ptr<ThreadPool> thread_pool_;
};

#endif // HTTP_SERVER_H