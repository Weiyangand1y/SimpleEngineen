#pragma once

#include <iostream>
#include <any>
#include <vector>
#include <unordered_map>
#include <functional>
#include <string>

using Info = std::vector<std::any>;
using Callback = std::function<void(Info&)>;
using Callbackn = std::function<void(void)>;

class SignalObject {
    std::unordered_map<std::string, std::vector<Callback>> signal_map;

public:
    SignalObject();

    void connect(std::string signal_name, Callback callback);

    void connect(std::string signal_name, Callbackn callback);

    void emit(std::string signal_name, Info info);

    void emit(std::string signal_name);

};

class InfoWrapper {
    int index = 0;

public:
    Info& info;

    InfoWrapper(Info& p_info);

    template<typename T>
    T get_next_value();

};

template<typename T>
T get_value(std::vector<std::any>& info, int index);
