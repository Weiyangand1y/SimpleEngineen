#pragma once
#include <iostream>
#include <functional>
template <typename ...Args>
class SignalObject {
    int get_next_id();
public:
    SignalObject();
    int connect(std::function<void(Args ...args));
    void disconnect(int id);
    void emit();
};