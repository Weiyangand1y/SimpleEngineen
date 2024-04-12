#include "Config.h"
#include "L1/Debug/Log.h"
#include <iostream>

void Config::init() {
    Logger::log(1,"Config init");
    data={
        {"shader_base_path", "C:/Users/21wyc/Documents/Project/SimpleEngine/assets/Shader/"},
        {"lua_script_file",  "C:/Users/21wyc/Documents/Project/SimpleEngine/assets/Script/"}
    };
    lua.script_file(data["lua_script_file"]+"config.lua");
    data["title"]=lua.get_or<std::string>("title","Simple Game Engineen");
    data["icon_path"]=lua.get_or<std::string>("icon_path","C:/Users/21wyc/Pictures/Camera Roll/searchPicture.png");
    data["font_path"]=lua.get_or<std::string>("font_path","C:/Users/21wyc/Pictures/font/tiny_font-master/Alibaba-PuHuiTi-Heavy.ttf");
    data["start_screen_image"]=lua.get_or<std::string>("start_screen_image","");
}

Config::Config() {
    init();
}

Config& Config::getInstance() {
    static Config instance; 
    return instance;
}

void Config::set(const std::string& key, const std::string& value) {
    data[key] = value;
}

void Config::do_for_kv_list(const std::string& key,std::function<void(std::string, std::string)> call) {
    sol::table imagePaths = lua[key];
    imagePaths.for_each([&](sol::object key, sol::object value) {
        std::string imageName = key.as<std::string>();
        std::string imagePath = value.as<std::string>();
        call(imageName,imagePath);
    });
}

std::string Config::get(const std::string& key) {
    if (data.find(key) != data.end()) {
            return data[key];
    }
    return ""; // 如果键不存在，返回空字符串
}

std::tuple<int, int> Config::get_windows_size() {
    int w=lua["window_size"]["w"];
    int h=lua["window_size"]["h"];
    return std::tuple<int, int>(w,h);
}
