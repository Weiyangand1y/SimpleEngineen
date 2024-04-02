#pragma once
#include "sol/sol.hpp"
class ScriptObject{ 
public:
    sol::state script;
    ScriptObject();
    void execute(const std::string& file_path);
    void bind(const std::string& key,std::function<void(void)> func);
    void script_function(int x);
    
};