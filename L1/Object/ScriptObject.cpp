#include "ScriptObject.h"
#include "L1/App/Config.h"

ScriptObject::ScriptObject() {
    script.open_libraries(sol::lib::base);
    //lua.script_file(Config::getInstance().get("lua_script_file")+"test1.lua");
}

void ScriptObject::execute(const std::string& file_path) {
    script.script_file(file_path);
}

void ScriptObject::bind(const std::string& key,std::function<void(void)> func) {
    script[key]=func;
}

void ScriptObject::script_function(int x) {
    std::cout << "Member function called with value: " << x << std::endl;
}
