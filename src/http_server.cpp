#include "http_server.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

HttpServer::HttpServer(int port, int thread_count)
    : port_(port), server_socket_(-1), running_(false),
      thread_pool_(std::make_unique<ThreadPool>(thread_count))
{
}

HttpServer::~HttpServer()
{
    stop();
}

void HttpServer::start()
{
    server_socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket_ < 0)
    {
        throw std::runtime_error("Failed to create socket");
    }

    int opt = 1;
    if (setsockopt(server_socket_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        close(server_socket_);
        throw std::runtime_error("Failed to set socket options");
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port_);

    if (bind(server_socket_, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        close(server_socket_);
        throw std::runtime_error("Failed to bind socket");
    }

    if (listen(server_socket_, 10) < 0)
    {
        close(server_socket_);
        throw std::runtime_error("Failed to listen on socket");
    }

    running_ = true;
    std::cout << "Server started on port " << port_ << std::endl;

    while (running_)
    {
        sockaddr_in client_addr{};
        socklen_t client_len = sizeof(client_addr);
        int client_socket = accept(server_socket_, (struct sockaddr *)&client_addr, &client_len);

        if (client_socket < 0)
        {
            if (running_)
            {
                std::cerr << "Failed to accept connection" << std::endl;
            }
            continue;
        }

        thread_pool_->enqueue([this, client_socket]()
                              { this->handleClient(client_socket); });
    }
}

void HttpServer::stop()
{
    running_ = false;
    if (server_socket_ >= 0)
    {
        close(server_socket_);
        server_socket_ = -1;
    }
}

void HttpServer::handleClient(int client_socket)
{
    char buffer[4096];
    ssize_t bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);

    if (bytes_read > 0)
    {
        buffer[bytes_read] = '\0';
        std::string request(buffer);
        std::string path = parseRequest(request);

        std::string response;
        if (path == "/")
        {
            std::string body = R"(
<!DOCTYPE html>
<html>
<head><title>C++ HTTP Server</title></head>
<body>
    <h1>Welcome to C++ HTTP Server!</h1>
    <p>This is a multi-threaded HTTP server built with C++</p>
    <ul>
        <li><a href="/about">About</a></li>
        <li><a href="/stats">Stats</a></li>
    </ul>
</body>
</html>
)";
            response = buildResponse(200, "text/html", body);
        }
        else if (path == "/about")
        {
            std::string body = R"(
<!DOCTYPE html>
<html>
<head><title>About</title></head>
<body>
    <h1>About This Server</h1>
    <p>Multi-threaded HTTP Server</p>
    <p>Built with: C++, POSIX Sockets, Thread Pool</p>
    <p><a href="/">Home</a></p>
</body>
</html>
)";
            response = buildResponse(200, "text/html", body);
        }
        else if (path == "/stats")
        {
            std::string body = R"(
<!DOCTYPE html>
<html>
<head><title>Stats</title></head>
<body>
    <h1>Server Statistics</h1>
    <p>Server is running smoothly!</p>
    <p><a href="/">Home</a></p>
</body>
</html>
)";
            response = buildResponse(200, "text/html", body);
        }
        else
        {
            std::string body = "<h1>404 Not Found</h1>";
            response = buildResponse(404, "text/html", body);
        }

        write(client_socket, response.c_str(), response.length());
    }

    close(client_socket);
}

std::string HttpServer::parseRequest(const std::string &request)
{
    std::istringstream iss(request);
    std::string method, path, version;
    iss >> method >> path >> version;
    return path;
}

std::string HttpServer::buildResponse(int status_code, const std::string &content_type,
                                      const std::string &body)
{
    std::ostringstream oss;
    std::string status_text = (status_code == 200) ? "OK" : "Not Found";

    oss << "HTTP/1.1 " << status_code << " " << status_text << "\r\n";
    oss << "Content-Type: " << content_type << "\r\n";
    oss << "Content-Length: " << body.length() << "\r\n";
    oss << "Connection: close\r\n";
    oss << "\r\n";
    oss << body;

    return oss.str();
}

std::string HttpServer::getContentType(const std::string &path)
{
    if (path.ends_with(".html"))
        return "text/html";
    if (path.ends_with(".css"))
        return "text/css";
    if (path.ends_with(".js"))
        return "application/javascript";
    if (path.ends_with(".json"))
        return "application/json";
    return "text/plain";
}

std::string HttpServer::readFile(const std::string &path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        return "";
    }

    std::ostringstream content;
    content << file.rdbuf();
    return content.str();
}