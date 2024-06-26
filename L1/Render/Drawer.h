//绘图指令
#pragma once
#include "L1/Render/Renderer.h"
#include <string>
class Drawer{
private:
    Render* renderer;
public:    
    Drawer();
    void draw_test();
    void set_render(Render& renderer);
    void draw_triangle();
    void draw_triangle(float x,float y,float sx=1.f,float sy=1.f);

    void draw_rect();
    void draw_rect(const float* mat4_data);
    void draw_rect(const float* mat4_data,float r,float g,float b,float a);
    void draw_texture(std::string id,float x=0.f,float y=0.f);
    void draw_texture(int id,const float* mat4_data);
    void draw_texture(std::string id,const float* mat4_data);
    void draw_texture(int texture_id,std::string shader_name="rect_texture");
    void draw_circle(const float* mat4_data,float r,float g,float b,float a=0.4f);

    void draw_cube(const float* m,const float* v,const float* p,std::string key);
};