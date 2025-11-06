# Multi-threaded HTTP Server in C++

[![Language](https://img.shields.io/badge/language-C++-blue.svg)](https://isocpp.org/)
[![Standard](https://img.shields.io/badge/C++-20-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B20)
[![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS-lightgrey.svg)](https://github.com/chowhanm25/cpp-http-server)

A lightweight, high-performance multi-threaded HTTP server implementation in C++ demonstrating advanced system programming concepts including socket programming, thread pools, and network I/O handling.

## 🚀 Features

- **Multi-threaded Architecture**: Efficient thread pool pattern for handling concurrent connections
- **POSIX Socket Programming**: Low-level network programming using system calls
- **HTTP/1.1 Support**: Basic HTTP server with GET request handling
- **Configurable**: Adjustable port and thread pool size via command-line arguments
- **Signal Handling**: Graceful shutdown on interrupt signals (Ctrl+C)
- **Cross-platform**: Compatible with Linux and macOS systems
- **Modern C++**: Utilizes C++20 features including smart pointers and RAII principles

## 📁 Project Structure

```
cpp-http-server/
├── src/
│   ├── main.cpp           # Application entry point and signal handling
│   ├── http_server.cpp    # HTTP server implementation (socket ops, request handling)
│   └── thread_pool.cpp    # Thread pool implementation for concurrent processing
├── include/
│   ├── http_server.h      # HTTP server class definition
│   └── thread_pool.h      # Thread pool class definition and templates
├── build/                 # Build output directory (generated)
├── tests/                 # Test files (future use)
├── CMakeLists.txt         # CMake build configuration
├── .gitignore            # Git ignore rules
└── README.md             # Project documentation
```

## 🛠️ Prerequisites

Before building this project, ensure you have:

- **C++ Compiler**: GCC 10+, Clang 10+, or MSVC 2019+ with C++20 support
- **CMake**: Version 3.10 or higher
- **POSIX-compliant OS**: Linux, macOS, or WSL (Windows Subsystem for Linux)
- **Git**: For version control

### Installing Prerequisites

**macOS:**
```bash
# Install Xcode Command Line Tools
xcode-select --install

# Install CMake via Homebrew
brew install cmake
```

**Linux (Ubuntu/Debian):**
```bash
sudo apt update
sudo apt install build-essential cmake git
```

## 🔧 Building the Project

### Clone the Repository
```bash
git clone https://github.com/chowhanm25/cpp-http-server.git
cd cpp-http-server
```

### Build Steps
```bash
# Create and navigate to build directory
mkdir build
cd build

# Generate build files using CMake
cmake ..

# Compile the project
make

# The executable 'http_server' will be created in the build directory
```

## 🎯 Usage

### Running the Server

**Default configuration** (port 8080, 4 worker threads):
```bash
./http_server
```

**Custom configuration**:
```bash
./http_server [port] [threads]

# Examples:
./http_server 9000           # Port 9000, 4 threads (default)
./http_server 8080 8         # Port 8080, 8 threads
./http_server 3000 16        # Port 3000, 16 threads
```

### Stopping the Server
Press `Ctrl+C` in the terminal to gracefully shutdown the server.

## 🌐 Testing the Server

### Using a Web Browser
Navigate to:
- **Home page**: http://localhost:8080/
- **About page**: http://localhost:8080/about
- **Stats page**: http://localhost:8080/stats

### Using curl
```bash
# Basic GET request
curl http://localhost:8080/

# Test about page
curl http://localhost:8080/about

# Test non-existent page (404)
curl http://localhost:8080/nonexistent
```

### Load Testing with Apache Bench
```bash
# Install Apache Bench (if not already installed)
# macOS: brew install httpd
# Linux: sudo apt install apache2-utils

# Run load test: 1000 requests, 100 concurrent
ab -n 1000 -c 100 http://localhost:8080/
```

### Using wget
```bash
wget http://localhost:8080/ -O output.html
```

## 💡 Technical Concepts Demonstrated

This project showcases several important system programming and software engineering concepts:

### 1. **Network Programming**
- Creating and configuring TCP sockets
- Binding sockets to network interfaces
- Listening for incoming connections
- Accepting client connections

### 2. **Multi-threading & Concurrency**
- Thread pool design pattern
- Work queue management
- Thread synchronization with mutexes
- Condition variables for thread coordination

### 3. **HTTP Protocol**
- HTTP request parsing (method, path, headers)
- HTTP response construction (status codes, headers, body)
- Content-Type handling

### 4. **Modern C++ Features**
- Smart pointers (`std::unique_ptr`, `std::shared_ptr`)
- RAII (Resource Acquisition Is Initialization)
- Template metaprogramming
- Move semantics
- Lambda functions

### 5. **System Programming**
- POSIX system calls (`read`, `write`, `close`)
- Signal handling (`SIGINT`, `SIGTERM`)
- File descriptors management
- Error handling

## 📚 Code Overview

### Main Components

**HttpServer Class** (`http_server.h/cpp`)
- Manages server lifecycle (start/stop)
- Handles socket operations
- Routes incoming requests
- Delegates work to thread pool

**ThreadPool Class** (`thread_pool.h/cpp`)
- Maintains a pool of worker threads
- Manages task queue
- Provides thread-safe task enqueueing
- Handles graceful shutdown

**Main Function** (`main.cpp`)
- Parses command-line arguments
- Sets up signal handlers
- Initializes and starts the server

## 🔮 Future Enhancements

Potential features to add:

- [ ] **POST/PUT/DELETE** request support
- [ ] **Static file serving** from a public directory
- [ ] **URL routing system** with regex support
- [ ] **Request/Response logging** with timestamps
- [ ] **HTTPS support** using OpenSSL
- [ ] **Configuration file** (JSON/YAML)
- [ ] **Keep-alive connections** (persistent HTTP)
- [ ] **Middleware support** for request/response processing
- [ ] **WebSocket support**
- [ ] **Unit tests** using Google Test framework
- [ ] **Docker containerization**
- [ ] **Performance metrics** and monitoring
- [ ] **Rate limiting** and DDoS protection

## 🐛 Troubleshooting

### Port Already in Use
```bash
# Find process using port 8080
lsof -i :8080

# Kill the process
kill -9 <PID>
```

### Permission Denied (ports < 1024)
```bash
# Use port > 1024 or run with sudo (not recommended)
./http_server 8080  # Safe
sudo ./http_server 80  # Requires root
```

### Compilation Errors
```bash
# Clean build directory
cd build
rm -rf *
cmake ..
make
```

## 📖 Learning Resources

- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)
- [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)
- [HTTP/1.1 RFC 2616](https://www.rfc-editor.org/rfc/rfc2616)
- [C++20 Features](https://en.cppreference.com/w/cpp/20)

## 📄 License

This project is licensed under the MIT License - feel free to use it for learning, personal projects, or commercial applications.

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request. For major changes:

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 👨‍💻 Author

**Munna Chowhan**
- GitHub: [@chowhanm25](https://github.com/chowhanm25)
- Project Link: [https://github.com/chowhanm25/cpp-http-server](https://github.com/chowhanm25/cpp-http-server)

## 🙏 Acknowledgments

- Thanks to the C++ community for excellent documentation
- Inspired by various open-source HTTP server implementations
- Built as a learning project to understand system programming concepts

---

⭐ **If you find this project helpful, please consider giving it a star!**
