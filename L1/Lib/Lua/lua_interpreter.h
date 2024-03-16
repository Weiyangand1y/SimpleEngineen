#pragma once
extern "C" {
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}
#include "../IO/textLoader.h"
#include <string>
#include <fstream>
#include <iostream>

class LuaInterpreter {
public:
    LuaInterpreter();

    ~LuaInterpreter() {
        lua_close(L);
    }

    void loadFile(const std::string& filename);

    void executeCode(const std::string& code);

private:
    lua_State* L;
};