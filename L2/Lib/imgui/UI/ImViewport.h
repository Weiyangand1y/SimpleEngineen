#pragma once
#include "imgui.h"
#include <string>
#include <functional>

class ImViewport{
public:
    std::string title="运行界面";
    int texture_id=0;
    std::function<void(float,float)> mouse_click_callback;
    void show();
};