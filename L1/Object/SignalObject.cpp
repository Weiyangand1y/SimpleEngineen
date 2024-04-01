#include "SignalObject.h"
#include "L1/Debug/Log.h"
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

void SignalObject::emit(std::string signal_name, const Info& info) {
    if(signal_map.find(signal_name)==signal_map.end()){
        debug("no: { }\n",signal_name);
        return;
    }
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

int SignalObject::connect_to_emit(std::string signal_name,
                                   SignalObject& other_signal_object,
                                   std::string other_signal_name) {
    int return_id = connect(signal_name, [&other_signal_object, other_signal_name](const Info& info) {
        other_signal_object.emit(other_signal_name, info);
    });
    return return_id;
    }

InfoWrapper::InfoWrapper(Info& p_info) : info(p_info) {}




