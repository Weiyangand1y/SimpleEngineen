#include "lua_read_data.h"
LuaReadData::LuaReadData(const std::string& filename) {
    L = luaL_newstate();
    luaL_openlibs(L);
    if (luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 0, 0)) {
        throw std::runtime_error(lua_tostring(L, -1));
    }
}
LuaReadData::~LuaReadData() {
    lua_close(L);
}
std::string LuaReadData::get_string(const std::string& varname) {
    lua_getglobal(L, varname.c_str());
    if (!lua_isstring(L, -1)) {
        throw std::runtime_error("'" + varname + "' is not a string");
    }
    std::string str_val = lua_tostring(L, -1);
    lua_pop(L, 1);  // 弹出栈顶元素
    return str_val;
}