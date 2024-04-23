#include <iostream>
#include <string>
#include <asio.hpp>

using asio::ip::tcp;

class GameClient {
public:
    GameClient() : io_context_(), socket_(io_context_), resolver_(io_context_) {}

    void init(const std::string& server_address, const std::string& port) {
        asio::connect(socket_, resolver_.resolve(server_address, port));
    }

    virtual void handleRead(const std::string& message) = 0;
    virtual void handleError(const std::string& error_message) = 0;

    void startAsyncRead() {
        asio::async_read_until(socket_, receive_buffer_, "\n",
            [this](std::error_code ec, std::size_t length) {
                if (!ec) {
                    std::istream is(&receive_buffer_);
                    std::string received_message;
                    std::getline(is, received_message, '\n'); // Read until '\0'
                    handleRead(received_message);

                    // Continue reading
                    startAsyncRead();
                } else {
                    handleError(ec.message());
                }
            });
    }

    void sendMessage(const std::string& message) {
        asio::async_write(socket_, asio::buffer(message.c_str(), message.size() + 1), // Include '\0' in buffer
            [this](std::error_code ec, std::size_t /*length*/) {
                if (ec) {
                    handleError(ec.message());
                }
            });
    }

    void poll() {
        io_context_.poll();
    }

protected:
    asio::io_context io_context_;
    tcp::socket socket_;
    tcp::resolver resolver_;
    asio::streambuf receive_buffer_;
};

class MyGameClient : public GameClient {
public:
    using GameClient::GameClient; // inherit constructors
    std::function<void(const std::string&)> read_callback=nullptr;
    void handleRead(const std::string& message) override {
        std::cout << "Received message from server: " << message << std::endl;
        // Add your custom handling code here
        if(read_callback)read_callback(message);
    }

    void handleError(const std::string& error_message) override {
        std::cerr << "Error: " << error_message << std::endl;
        // Add your custom error handling code here
    }
};

