#include <iostream>
#include <asio.hpp>

using namespace asio;

class TcpServer {
public:
    std::function<void(const std::string&)> read_callback = nullptr;
    TcpServer() : io_context_(), acceptor_(io_context_), socket_(io_context_) {}

    void init(short port) {
        ip::tcp::endpoint endpoint(ip::tcp::v4(), port);
        acceptor_.open(endpoint.protocol());
        acceptor_.set_option(ip::tcp::acceptor::reuse_address(true));
        acceptor_.bind(endpoint);
        acceptor_.listen();
        acceptConnection();
    }

    void startListening(short port) {
        ip::tcp::endpoint endpoint(ip::tcp::v4(), port);
        acceptor_.open(endpoint.protocol());
        acceptor_.set_option(ip::tcp::acceptor::reuse_address(true));
        acceptor_.bind(endpoint);
        acceptor_.listen();
        acceptConnection();
    }

    void stopListening() {
        acceptor_.close();
        // 关闭已建立的连接
        socket_.close();
    }

    void poll() {
        io_context_.poll();
    }

    void sendMessage(const std::string& message) {
        asio::async_write(socket_, asio::buffer(message.c_str(), message.size() + 1), // Include '\0' in buffer
            [this](std::error_code ec, std::size_t /*length*/) {
                if (ec) {
                    std::cerr << "S:Error sending message: " << ec.message() << std::endl;
                }
            });
    }

private:
    void acceptConnection() {
        acceptor_.async_accept(socket_, [this](auto ec) {
            if (!ec) {
                std::cout << "S:New connection established" << std::endl;
                handleRequest();
            } else {
                std::cerr << "S:Error accepting connection: " << ec.message() << std::endl;
            }
        });
    }

    void handleRequest() {
        if (acceptor_.is_open()) {
            async_read_until(socket_, buffer_, '\n', [this](auto ec, std::size_t length) {
                if (!ec) {
                    std::istream is(&buffer_);
                    std::string line;
                    std::getline(is, line);
                    is.get();//读取\0
                    std::cout << "S:Received: " << line << std::endl;
                    if (read_callback) read_callback(line);
                    handleRequest(); // 继续处理下一个请求
                } else {
                    std::cerr << "S:Error reading: " << ec.message() << std::endl;
                    // 关闭当前套接字，但保持服务器能够接受新连接
                    socket_.close();
                    acceptConnection(); // 重新接受新连接
                }
            });
        }
    }

private:
    io_context io_context_;
    ip::tcp::acceptor acceptor_;
    ip::tcp::socket socket_;
    streambuf buffer_;
};
