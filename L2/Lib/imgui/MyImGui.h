#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <unordered_map>
#include <string>
class MyImGui{
private:
public:
    static void static_init(GLFWwindow* window);
    static void static_begin();
    static void static_end();
    static ImFont* get_imfont(int index);
    static int count;
    static std::unordered_map<std::string, ImFont*> font_map;
    MyImGui();
    
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
