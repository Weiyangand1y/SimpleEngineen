#include <iostream>
#include <functional>
#include <map>
#include <vector>
#include <cstdarg>

class SignalEmitter {
public:
    void emit(const std::string& signal, ...) {
        auto it = connections.find(signal);
        if (it != connections.end()) {
            va_list args;
            va_start(args, signal);
            for (auto& func : it->second) {
                func(args);
            }
            va_end(args);
        }
    }

    template<typename Func>
    void connect(const std::string& signal, Func&& func) {
        connections[signal].emplace_back([func](va_list args) {
            func(args);
        });
    }

private:
    std::map<std::string, std::vector<std::function<void(va_list)>> > connections;
};

void myFunction(int arg1, double arg2, int arg3) {
    std::cout << "Received args: " << arg1 << ", " << arg2 << ", " << arg3 << std::endl;
}

int main() {
    SignalEmitter emitter;
    emitter.connect("example_signal", myFunction);

    emitter.emit("example_signal", 42, 3.14);

    return 0;
}