#pragma once
extern "C" {
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}
#include <iostream>
class LuaParser {
public:
    LuaParser() {
        L = luaL_newstate(); // 创建Lua解析器
        luaL_openlibs(L); // 打开Lua标准库
    }

    ~LuaParser() {
        lua_close(L); // 关闭Lua解析器
    }

    bool loadScript(const char* filename) {
        return luaL_dofile(L, filename) == LUA_OK; // 加载Lua脚本
    }

    template<typename... Args>
    bool callFunction(const char* name, Args&&... args) {
        lua_getglobal(L, name); // 获取全局函数
        if (!lua_isfunction(L, -1)) { // 如果不是函数
            lua_pop(L, 1); // 弹出栈顶元素
            return false; // 返回失败
        }
        pushArgs(std::forward<Args>(args)...); // 压入参数
        if (lua_pcall(L, sizeof...(args), 1, 0) != LUA_OK) { // 调用函数
            lua_pop(L, 1); // 弹出栈顶元素
            return false; // 返回失败
        }
        return true; // 返回成功
    }

    template<typename T>
    T getReturnValue() {
        T result = readValue<T>(lua_gettop(L)); // 读取返回值
        lua_pop(L, 1); // 弹出栈顶元素
        return result; // 返回值
    }

private:
    lua_State* L;

    void pushArgs() {}

    template<typename T, typename... Args>
    void pushArgs(T&& arg, Args&&... args) {
        pushValue(std::forward<T>(arg)); // 压入参数
        pushArgs(std::forward<Args>(args)...); // 压入剩余参数
    }

    void pushValue(const char* value) {
        lua_pushstring(L, value); // 压入字符串
    }

    void pushValue(int value) {
        lua_pushinteger(L, value); // 压入整数
    }

    void pushValue(double value) {
        lua_pushnumber(L, value); // 压入浮点数
    }

    template<typename T>
    T readValue(int index) {}

    template<>
    const char* readValue<const char*>(int index) {
        return lua_tostring(L, index); // 读取字符串
    }

    template<>
    int readValue<int>(int index) {
        return lua_tointeger(L, index); // 读取整数
    }

    template<>
    double readValue<double>(int index) {
        return lua_tonumber(L, index); // 读取浮点数
    }

    // 静态函数，用于包装成员函数
    static int memberFunctionWrapper(lua_State* L) {
        LuaParser* self = static_cast<LuaParser*>(lua_touserdata(L, lua_upvalueindex(1))); // 获取对象指针
        if (self) {
            // 调用成员函数
            return self->memberFunction(lua_tostring(L, 1), lua_tointeger(L, 2), lua_tonumber(L, 3));
        }
        return 0;
    }

    // 成员函数
    int memberFunction(const char* str, int num, double dbl) {
        std::cout << "String: " << str << std::endl;
        std::cout << "Number: " << num << std::endl;
        std::cout << "Double: " << dbl << std::endl;
        return num + static_cast<int>(dbl);
    }

public:
    // 注册成员函数
    void registerMemberFunction(const char* name) {
        lua_pushstring(L, name); // 压入函数名
        lua_pushlightuserdata(L, this); // 压入对象指针
        lua_pushcclosure(L, memberFunctionWrapper, 1); // 压入闭包
        lua_setglobal(L, name); // 设置全局函数
    }
};