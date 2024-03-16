#include "SignalObject.h"

SignalObject::SignalObject() {}

void SignalObject::connect(std::string signal_name, Callback callback) {
    std::vector<Callback>& list = signal_map[signal_name];
    list.push_back(callback);
}

void SignalObject::connect(std::string signal_name, Callbackn callback) {
    Callback cb = [&](Info info) {
        info.resize(0);
        callback();
    };
    std::vector<Callback>& list = signal_map[signal_name];
    list.push_back(cb);
}

void SignalObject::emit(std::string signal_name, Info info) {
    std::vector<Callback>& list = signal_map[signal_name];
    for (size_t i = 0; i < list.size(); i++) {
        list[i](info);
    }
}

void SignalObject::emit(std::string signal_name) {
    Info info;
    std::vector<Callback>& list = signal_map[signal_name];
    for (size_t i = 0; i < list.size(); i++) {
        list[i](info);
    }
}

InfoWrapper::InfoWrapper(Info& p_info) : info(p_info) {}

template<typename T>
T InfoWrapper::get_next_value() {
    return std::any_cast<T>(info[index++]);
}

template<typename T>
T get_value(std::vector<std::any>& info, int index) {
    return std::any_cast<T>(info[index]);
}


