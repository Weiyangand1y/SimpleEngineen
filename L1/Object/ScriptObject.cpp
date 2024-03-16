#include "ScriptObject.h"
#include "L1/App/Config.h"

ScriptObject::ScriptObject() {
    lua.open_libraries(sol::lib::base);
    lua.new_usertype<ScriptObject>("MyClass",
            "doFunction", &ScriptObject::script_function
    );        
    lua.set("myObject", this);
    lua.script_file(Config::getInstance().get("lua_script_file")+"test1.lua");
}

void ScriptObject::script_function(int x) {
    std::cout << "Member function called with value: " << x << std::endl;
}
