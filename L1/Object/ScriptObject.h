#pragma once
#include "sol/sol.hpp"
class ScriptObject{
    sol::state lua;
public:
    ScriptObject();
    void script_function(int x);
};