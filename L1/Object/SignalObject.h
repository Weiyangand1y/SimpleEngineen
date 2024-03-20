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

struct PairIdCallback{
    int id=0;
    Callback callbak;
};

class SignalObject {
    std::unordered_map<std::string, std::vector<PairIdCallback>> signal_map;
    int get_next_id(std::string signal_name);
public:
    SignalObject();

    int connect(std::string signal_name, Callback callback);

    void connect(std::string signal_name, Callbackn callback);

    void disconnect(std::string signal_name, int id);

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

template<typename T>
T InfoWrapper::get_next_value() {
    return std::any_cast<T>(info[index++]);
}

template<typename T>
T get_value(std::vector<std::any>& info, int index) {
    return std::any_cast<T>(info[index]);
}