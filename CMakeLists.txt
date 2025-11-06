cmake_minimum_required(VERSION 3.10)
project(HTTPServer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(http_server
    src/main.cpp
    src/http_server.cpp
    src/thread_pool.cpp
)

find_package(Threads REQUIRED)
target_link_libraries(http_server Threads::Threads)
