#include <iostream>
#include <string>
#include <asio.hpp>

using asio::ip::tcp;

class GameClient {
public:
    GameClient(const std::string& server_address, const std::string& port)
        : io_context_(), socket_(io_context_), resolver_(io_context_) {
        asio::connect(socket_, resolver_.resolve(server_address, port));
    }

    virtual void handleRead(const std::string& message) = 0;
    virtual void handleError(const std::string& error_message) = 0;

    void start_async_read() {
        asio::async_read_until(socket_, receive_buffer_, "\n",
            [this](std::error_code ec, std::size_t length) {
                if (!ec) {
                    std::istream is(&receive_buffer_);
                    std::string received_message;
                    std::getline(is, received_message, '\n'); // Read until '\0'
                    handleRead(received_message);

                    // Continue reading
                    start_async_read();
                } else {
                    handleError(ec.message());
                }
            });
    }

    void send_message(const std::string& message) {
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

    void handleRead(const std::string& message) override {
        std::cout << "Received message from server: " << message << std::endl;
        // Add your custom handling code here
    }

    void handleError(const std::string& error_message) override {
        std::cerr << "Error: " << error_message << std::endl;
        // Add your custom error handling code here
    }
};

int main() {
    MyGameClient client("127.0.0.1", "8888");
    client.start_async_read();
    
    // Example usage of poll()
    while (true) {
        client.poll();
        // Add your other application logic here
    }

    return 0;
}
