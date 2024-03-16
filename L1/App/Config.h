#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <tuple>
class Config {
private:
    std::unordered_map<std::string, std::string> data;
    void init();
    Config();

public:
    static Config& getInstance();
    void set(const std::string& key, const std::string& value);
    std::string get(const std::string& key);
    std::tuple<int,int> get_windows_size();
};
