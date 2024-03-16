#include "lua_interpreter.h"
LuaInterpreter::LuaInterpreter() {
        L = luaL_newstate();
        luaL_openlibs(L);
    }

void LuaInterpreter::loadFile(const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string script=loadTextFile(filename);
            luaL_loadstring(L, script.c_str());
            lua_pcall(L, 0, 0, 0);
            file.close();
        } else {
            std::cerr << "Error: Unable to open file" << std::endl;
        }
    }

void LuaInterpreter::executeCode(const std::string& code) {
        luaL_loadstring(L, code.c_str());
        lua_pcall(L, 0, 0, 0);
    }