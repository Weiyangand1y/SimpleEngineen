#include "Drawer3D.h"
#include "L1/App/Config.h"

Drawer3D::Drawer3D(){
    
}

void Drawer3D::draw_cube(float* model_matrix) {
    simple_cube_shader->use();
    simple_cube_shader->setMat4("model",model_matrix);
    renderer->use_vertex(Render::VertexType::TEX_CUBE);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
void Drawer3D::draw_light_cube(float* model_matrix) {
    light_cube_shader.use();
    light_cube_shader.setMat4("model",model_matrix);
    renderer->use_vertex(Render::VertexType::NORMAL_TEX_CUBE);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Drawer3D::set_renderer(Render& p_render) {
    renderer=&p_render;
    init_shader();
}

void Drawer3D::init_shader() {
    ubo.init(MATRIX_SIZE*2);
    ubo.add_layout(MATRIX_SIZE);
    ubo.add_layout(MATRIX_SIZE);
    
    simple_cube_shader=&renderer->get_shader("simple_cube");
    simple_cube_shader->use();
    renderer->use_texture("p1",0);
    renderer->use_texture("Pippi_Carter",1);
    simple_cube_shader->setInt("texture1",0);
    simple_cube_shader->setInt("texture2",1);
    //
    std::string base_path=Config::getInstance().get("shader_base_path");
    renderer->get_shader_db().load_from_file("light_cube",
        base_path+"box/box_normal.vert",
        base_path+"light/light_material.frag");
    light_cube_shader=renderer->get_shader("light_cube");
    light_cube_shader.use();
    light_cube_shader.setFloat3("objectColor",1.0f, 0.5f, 0.31f);
    light_cube_shader.setFloat3("lightColor",  1.0f, 1.0f, 1.0f);
    

    std::vector<Shader*> shader_list={
        simple_cube_shader,&light_cube_shader
    };
    std::for_each(shader_list.begin(),shader_list.end(),[&](Shader* s){
        ubo.bind_shader_uniform(s->id,"Matrices");
    });
}

void Drawer3D::change_view_matrix(float* view_matrix) {
    ubo.wrap_update(1,view_matrix);
}

void Drawer3D::change_projection_matrix(float* projection_matrix) {
    ubo.wrap_update(0,projection_matrix);
}

void Drawer3D::change_transform_matrix(float* transform_matrix) {
    simple_cube_shader->setMat4("model",transform_matrix);
}

void Drawer3D::chnage_view_pos(float x, float y, float z) {
    light_cube_shader.setFloat3("viewPos",x,y,z);
}

void Drawer3D::change_light_pos(float x, float y, float z) {
    light_cube_shader.setFloat3("lightPos",3.f,-10.f,5.f);
}
