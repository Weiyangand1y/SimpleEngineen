#pragma once
extern "C" {
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}
#include <string>
#include <stdexcept>

class LuaReadData {
public:
    LuaReadData(const std::string& filename);
    ~LuaReadData();
    std::string get_string(const std::string& varname);
private:
    lua_State* L;
};
