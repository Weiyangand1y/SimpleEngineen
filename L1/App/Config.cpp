#include "Config.h"

void Config::init() {
    data={
        {"icon_path","C:\\Users\\21wyc\\Pictures\\Camera Roll\\searchPicture.png"},
        {"shader_base_path",R"(C:\Users\21wyc\Documents\Project\GameMada\graphic\shader\)"},
        {"texture_base_path","C:/Users/21wyc/Pictures/"}
    };
}

Config::Config() {
    init();
}

Config& Config::getInstance() {
    static Config instance; // 在首次调用时初始化
    return instance;
}

void Config::set(const std::string& key, const std::string& value) {
    data[key] = value;
}

std::string Config::get(const std::string& key) {
    if (data.find(key) != data.end()) {
            return data[key];
    }
    return ""; // 如果键不存在，返回空字符串
}