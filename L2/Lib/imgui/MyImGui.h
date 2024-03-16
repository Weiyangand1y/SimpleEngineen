#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class MyImGui{
private:
    float color[3]={0.0};
    char text[20]={0};
public:
    static void static_init(GLFWwindow* window);
    static void static_begin();
    static void static_end();
    MyImGui();
    
    bool show_demo_window = true;
    bool show_another_window = true;
    void render();
};

