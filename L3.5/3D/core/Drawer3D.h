#pragma once
#include "L1/Render/Renderer.h"


/// @brief 该类是3D drawer， 可以让shader的一些uniform进行共享，减少数据传输的量，对比较有限的shader进行硬编码
class Drawer3D{
private:
    Render* renderer;
    Shader* simple_cube_shader;
public:
    Drawer3D();   
    void set_renderer(Render& render);
    void init_shader();
    void change_view_matrix(float* model_matrix);
    void change_projection_matrix(float* model_matrix);
    void change_transform_matrix(float* transform_matrix);
    void draw_cube(float* model_matrix);
};

