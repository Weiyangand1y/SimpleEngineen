#pragma once
#include "L1/Render/Renderer.h"
class ShaderDrawer{
private:
    Render* renderer;
public:
    ShaderDrawer();
    void set_render(Render& renderer);
    void draw(float* transform_mat,float time);
};


