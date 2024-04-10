#pragma once

#include <iostream>
#include <any>
#include <vector>
#include <unordered_map>
#include <functional>
#include <string>


using Info = std::vector<std::any>;
using Callback = std::function<void(const Info&)>;
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



    void disconnect(std::string signal_name, int id);

    void emit(std::string signal_name, const Info& info);

    void emit(std::string signal_name);
    //连接转发的封装，本质还是connect
    int connect_to_emit(std::string signal_name,SignalObject& other_signal_object,std::string other_signal_name);

};

class InfoWrapper {
    int index = 0;

public:
    Info& info;

    InfoWrapper(Info& p_info);

    template<typename T>
    T get_next_value();
    template<typename T>
    InfoWrapper& next(T& arg);
};

template<typename T>
T get_value(std::vector<std::any>& info, int index);

template<typename T>
T InfoWrapper::get_next_value() {
    return std::any_cast<T>(info[index++]);
}

template <typename T>
inline InfoWrapper& InfoWrapper::next(T& arg) {
    arg=std::any_cast<T>(info[index++]);
    return *this;
}

template<typename T>
T get_value(std::vector<std::any>& info, int index) {
    return std::any_cast<T>(info[index]);
}