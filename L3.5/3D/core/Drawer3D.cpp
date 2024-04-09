#include "Drawer3D.h"

Drawer3D::Drawer3D(){
    
}

void Drawer3D::draw_cube(float* model_matrix) {
    simple_cube_shader->use();
    simple_cube_shader->setMat4("model",model_matrix);
    renderer->use_vertex(Render::VertexType::TEX_CUBE);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Drawer3D::set_renderer(Render& p_render) {
    renderer=&p_render;
    init_shader();
}

void Drawer3D::init_shader() {
    simple_cube_shader=&renderer->get_shader("simple_cube");
    simple_cube_shader->use();
    renderer->use_texture("p1",0);
    renderer->use_texture("Pippi_Carter",1);
    simple_cube_shader->setInt("texture1",0);
    simple_cube_shader->setInt("texture2",1);
}

void Drawer3D::change_view_matrix(float* view_matrix) {
    simple_cube_shader->setMat4("view",view_matrix);
}

void Drawer3D::change_projection_matrix(float* model_matrix) {
    simple_cube_shader->setMat4("projection",model_matrix);
}

void Drawer3D::change_transform_matrix(float* transform_matrix) {
    simple_cube_shader->setMat4("model",transform_matrix);
}
