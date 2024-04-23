#include <iostream>
#include <asio.hpp>

using asio::ip::tcp;

class GameClient {
public:
    GameClient(asio::io_context& io_context, const std::string& server_address, const std::string& port)
        : socket_(io_context), io_context_(io_context)
    {
        tcp::resolver resolver(io_context);
        asio::connect(socket_, resolver.resolve(server_address, port));
    }

    void startAsyncRead() {
        asio::async_read_until(socket_, receive_buffer_, "\r\n",
            [this](std::error_code ec, std::size_t length) {
                if (!ec) {
                    std::istream is(&receive_buffer_);
                    std::string received_message;
                    std::getline(is, received_message, '\0'); // Read until '\0'
                    std::cout << "Received message from server: " << received_message << std::endl;

                    // Continue reading
                    startAsyncRead();
                } else {
                    std::cerr << "Error receiving message: " << ec.message() << std::endl;
                }
            });
    }

    void sendMessage(const std::string& message) {
        asio::async_write(socket_, asio::buffer(message.c_str(), message.size() + 1), // Include '\0' in buffer
            [this](std::error_code ec, std::size_t /*length*/) {
                if (!ec) {
                    //std::cout << "Message sent successfully!" << std::endl;
                } else {
                    std::cerr << "Error sending message: " << ec.message() << std::endl;
                }
            });
    }

private:
    tcp::socket socket_;
    asio::io_context& io_context_;
    asio::streambuf receive_buffer_;
};

int main() {
    try {
        asio::io_context io_context;

        // Connect to server
        GameClient client(io_context, "127.0.0.1", "12345");

        // Start asynchronous reading from the server
        client.startAsyncRead();

        // Main game loop
        while (true) {
            // Handle user input, update game state, render graphics, etc.

            // Example: sending player input to the server
            std::string player_input = "Player input";
            client.sendMessage(player_input);

            // Run asynchronous operations in the io_context
            io_context.poll();

            // Sleep or yield to control frame rate
            std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Example: 60 FPS
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
