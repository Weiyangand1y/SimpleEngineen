#pragma once
#include "imgui.h"
#include <string>
#include <functional>
#include "L1/Object/SignalObject.h"
class ImViewport{
public:
    SignalObject signal;
    std::string title="运行界面";
    int texture_id=0;
    std::function<void(float,float)> mouse_click_callback=nullptr;
    void drawGui();
};