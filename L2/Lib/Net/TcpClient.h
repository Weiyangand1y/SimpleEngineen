#include <iostream>
#include <string>
#include <asio.hpp>

using asio::ip::tcp;

class GameClient {
public:
    GameClient() : io_context_(), socket_(io_context_), resolver_(io_context_), connected_(false) {}

    void init(const std::string& server_address, const std::string& port) {
        server_address_ = server_address;
        port_ = port;
    }

    virtual void handleRead(const std::string& message) = 0;
    virtual void handleError(const std::string& error_message) = 0;

    void connect_to_server() {
        resolver_.async_resolve(server_address_, port_,
            [this](std::error_code ec, tcp::resolver::results_type endpoints) {
                if (!ec) {
                    asio::async_connect(socket_, endpoints,
                        [this](std::error_code ec, tcp::endpoint) {
                            if (!ec) {
                                connected_ = true;
                                start_async_read();
                            } else {
                                handleError(ec.message());
                            }
                        });
                } else {
                    handleError(ec.message());
                }
            });
    }

    void disconnect() {
        if (connected_) {
            socket_.close();
            connected_ = false;
        }
    }

    void reconnect(const std::string& server_address, const std::string& port) {
        disconnect();
        init(server_address, port);
        connect_to_server();
    }

    void start_async_read() {
        if (!connected_) {
            handleError("Not connected to server.");
            return;
        }
        asio::async_read_until(socket_, receive_buffer_, "\n",
            [this](std::error_code ec, std::size_t length) {
                if (!ec) {
                    std::istream is(&receive_buffer_);
                    std::string received_message;
                    std::getline(is, received_message, '\n'); // Read until '\0'
                    is.get();//读取\0
                    handleRead(received_message);

                    // Continue reading
                    start_async_read();
                } else {
                    handleError(ec.message());
                    disconnect();
                }
            });
    }

    void sendMessage(const std::string& message) {
        if (!connected_) {
            handleError("Not connected to server.");
            return;
        }
        asio::async_write(socket_, asio::buffer(message.c_str(), message.size() + 1), // Include '\0' in buffer
            [this](std::error_code ec, std::size_t /*length*/) {
                if (ec) {
                    handleError(ec.message());
                    disconnect();
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
    std::string server_address_;
    std::string port_;
    bool connected_;
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
