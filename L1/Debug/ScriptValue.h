#pragma once
#include "sol/sol.hpp"
// use in testxx.cpp
class ScriptValueGetter{
    sol::state script;
    static ScriptValueGetter* instance;
    ScriptValueGetter(){
        script.open_libraries(sol::lib::base);
        script.script_file("C:/Users/21wyc/Documents/Project/SimpleEngine/assets/Script/debug/values.lua");
    }
public:
    static ScriptValueGetter* getInstance() {
        // 如果实例为空，则创建一个新实例
        if (!instance) {
            instance = new ScriptValueGetter();
        }
        return instance;
    }
    float get_value(const std::string& key){
        return script[key].get_or<float,float>(1.f);
    }
};

ScriptValueGetter* ScriptValueGetter::instance=nullptr;