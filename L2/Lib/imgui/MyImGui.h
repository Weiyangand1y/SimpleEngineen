#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class MyImGui{
private:
public:
    static void static_init(GLFWwindow* window);
    static void static_begin();
    static void static_end();
    static ImFont* get_imfont(int index);
    static int count;
    MyImGui();
    
    bool show_demo_window = true;
    bool show_another_window = true;
    virtual void render();
};

static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs)
{ 
    return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); 
}
static inline void operator+=(ImVec2& lhs, const ImVec2& rhs)
{ 
    lhs.x+=rhs.x;
    lhs.y+=rhs.y;
}
static inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs)
{ 
    return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); 
}
static inline ImVec2 ImRotate(const ImVec2& v, float cos_a, float sin_a) 
{ 
    return ImVec2(v.x * cos_a - v.y * sin_a, v.x * sin_a + v.y * cos_a);
}
static inline ImVec2 operator*(const ImVec2& lhs, const ImVec2& rhs)
{ 
    return ImVec2(lhs.x * rhs.x, lhs.y * rhs.y); 
}
static inline ImVec2 operator*(const ImVec2& lhs, const float rhs)
{
    return ImVec2(lhs.x * rhs, lhs.y * rhs);
}


//
static inline float dot(const ImVec2& lhs, const ImVec2& rhs)
{ 
    return lhs.x * rhs.x + lhs.y * rhs.y; 
}
namespace ImGui{
    void ImageRotated(ImTextureID tex_id, ImVec2 center, ImVec2 size, float angle,ImVec4 uv={0,1,1,0});
}
