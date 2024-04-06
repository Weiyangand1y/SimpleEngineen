#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <tuple>
#include "sol/sol.hpp"
#include <functional>
class Config {
private:
    sol::state lua;
    std::unordered_map<std::string, std::string> data;
    void init();
    Config();

public:
    static Config& getInstance();
    void set(const std::string& key, const std::string& value);
    void do_for_kv_list(const std::string& key,std::function<void(std::string,std::string)> call);
    std::string get(const std::string& key);
    std::tuple<int,int> get_windows_size();

};
