#include "SignalObject.h"

int SignalObject::get_next_id(std::string signal_name) {
    auto& list=signal_map[signal_name];
    if(list.empty())return 0;
    else return list.back().id+1;
}

SignalObject::SignalObject() {}

int SignalObject::connect(std::string signal_name, Callback callback) {
    auto& list = signal_map[signal_name];
    int id=get_next_id(signal_name);
    list.push_back({id,callback});
    return id;
}

void SignalObject::connect(std::string signal_name, Callbackn callback) {
    Callback cb = [&](Info info) {
        info.resize(0);
        callback();
    };
    auto& list = signal_map[signal_name];
    list.push_back({get_next_id(signal_name),cb});
}

void SignalObject::disconnect(std::string signal_name, int id) {
    auto& list = signal_map[signal_name];
    auto it = std::find_if(list.begin(), list.end(), [id](const PairIdCallback& s) {
        return s.id == id;
    });

    if (it != list.end()) {
        list.erase(it);
    }
}

void SignalObject::emit(std::string signal_name, Info info) {
    auto& list = signal_map[signal_name];
    for (size_t i = 0; i < list.size(); i++) {
        list[i].callbak(info);
    }
}

void SignalObject::emit(std::string signal_name) {
    Info info;
    auto& list = signal_map[signal_name];
    for (size_t i = 0; i < list.size(); i++) {
        list[i].callbak(info);
    }
}

InfoWrapper::InfoWrapper(Info& p_info) : info(p_info) {}




