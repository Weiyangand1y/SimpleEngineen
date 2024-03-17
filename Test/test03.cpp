#include <httplib.h>
#include <iostream>
#include <thread>
int main(void) {
    std::thread th1([]() {
        httplib::Client cli("localhost", 1234);

        if (auto res = cli.Get("/hi")) {
            if (res->status == 200) {
                std::cout << res->body << std::endl;
            }
        } else {
            auto err = res.error();
            std::cout << "HTTP error: " << httplib::to_string(err) << std::endl;
        }
    });
    std::cout<<"----------------"<<std::endl;
    th1.join();
}