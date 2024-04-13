#include "Drawer3D.h"
#include "L1/App/Config.h"
#include "L1/Lib/Math/math.h"
#include "L3.5/3D/core/Object/Geometry.h"
#include "L1/Debug/Log.h"
Drawer3D::Drawer3D(){
    
}

void Drawer3D::draw_cube(float* model_matrix) {
    simple_cube_shader->use();
    simple_cube_shader->setMat4("model",model_matrix);
    renderer->use_texture("p1",0);
    simple_cube_shader->setInt("texture1",0);
    renderer->use_vertex(Render::VertexType::TEX_CUBE);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
void Drawer3D::draw_light_cube(float* model_matrix) {
    light_cube_shader.use();
    light_cube_shader.setMat4("model",model_matrix);
    light_cube_shader.use();
    Texture& container_texture=renderer->get_texture("container");
    container_texture.use(0);
    Texture& container_specular_texture=renderer->get_texture("container_specular");
    container_specular_texture.use(1);
    renderer->use_vertex(Render::VertexType::NORMAL_TEX_CUBE);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Drawer3D::draw_texture_plane(const std::string& texture_name,float* model_matrix) {
    renderer->use_vertex(Render::VertexType::TEX_RECT);
    simple_cube_shader->use();
    renderer->use_texture(texture_name,0);
    simple_cube_shader->setInt("texture1",0);
    simple_cube_shader->setMat4("model",model_matrix);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

void Drawer3D::draw_ruler(float* model_matrix,float r,float g,float b) {
    simple_color_cube_shader->use();    
    simple_color_cube_shader->setMat4("model",model_matrix);
    simple_color_cube_shader->setFloat3("color",r,g,b);
    renderer->use_vertex(Render::VertexType::NORMAL_TEX_CUBE);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Drawer3D::draw_ruler() {
    math::mat4 rm(1.f);
    float len=50.f,width=0.05f;
    Transform3D ta;
    ta.scale_local({len,width,width});
    draw_ruler(ta.get_matrix_ptr(),1.F,0.F,0.F);

    Transform3D tb;
    tb.scale_local({width,len,width});
    draw_ruler(tb.get_matrix_ptr(),0.F,1.F,0.F);

    Transform3D tc;
    tc.scale_local({width,width,len});
    draw_ruler(tc.get_matrix_ptr(),0.F,0.F,1.F);

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
    simple_cube_shader->setInt("texture1",0);
    //
    std::string base_path=Config::getInstance().get("shader_base_path");
    
    //light cube
    renderer->get_shader_db().load_from_file("light_cube",
        base_path+"box/box_normal.vert",
        base_path+"light/light_material.frag");
    light_cube_shader=renderer->get_shader("light_cube");
    light_cube_shader.use();
{    Texture& container_texture=renderer->get_texture("container");
    container_texture.use(0);
    Texture& container_specular_texture=renderer->get_texture("container_specular");
    container_specular_texture.use(1);
    light_cube_shader.setInt("material.diffuse",0);
    light_cube_shader.setInt("material.specular",1);
    light_cube_shader.setFloat("material.shininess", 32.0f);

    light_cube_shader.setFloat3("dirLight.direction", -0.2f, -1.0f, -0.3f);
    light_cube_shader.setFloat3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
    light_cube_shader.setFloat3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
    light_cube_shader.setFloat3("dirLight.specular", 0.5f, 0.5f, 0.5f);
    // point light 1
    light_cube_shader.setFloat3("pointLight.position", 0.f,0.f,0.f);
    light_cube_shader.setFloat3("pointLight.ambient", 0.05f, 0.05f, 0.05f);
    light_cube_shader.setFloat3("pointLight.diffuse", 0.8f, 0.8f, 0.8f);
    light_cube_shader.setFloat3("pointLight.specular", 1.0f, 1.0f, 1.0f);
    light_cube_shader.setFloat("pointLight.constant", 1.0f);
    light_cube_shader.setFloat("pointLight.linear", 0.09f);
    light_cube_shader.setFloat("pointLight.quadratic", 0.032f);

    light_cube_shader.setFloat3("spotLight.position", 0.f,0.f,0.f);
    light_cube_shader.setFloat3("spotLight.direction", 0,-1,0);
    light_cube_shader.setFloat3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
    light_cube_shader.setFloat3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
    light_cube_shader.setFloat3("spotLight.specular", 1.0f, 1.0f, 1.0f);
    light_cube_shader.setFloat("spotLight.constant", 1.0f);
    light_cube_shader.setFloat("spotLight.linear", 0.09f);
    light_cube_shader.setFloat("spotLight.quadratic", 0.032f);
    light_cube_shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    light_cube_shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f))); }
    
    
    renderer->get_shader_db().load_from_file("light_cube",
        base_path+"box/box_normal.vert",
        base_path+"box/simple_color.frag");
    simple_color_cube_shader=&renderer->get_shader("light_cube");
    simple_color_cube_shader->use();

    //model
    renderer->get_shader_db().load_from_file("model",
        base_path+"box/box_normal.vert",
        base_path+"model/model.frag"
    );
    model_shader=&renderer->get_shader("model");

    std::vector<Shader*> shader_list={
        simple_cube_shader,&light_cube_shader,simple_color_cube_shader,
        model_shader
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
    simple_cube_shader->use();
    simple_cube_shader->setMat4("model",transform_matrix);
}

void Drawer3D::chnage_view_pos(float x, float y, float z) {
    light_cube_shader.use();
    light_cube_shader.setFloat3("viewPos",x,y,z);
}

void Drawer3D::change_light_pos(float x, float y, float z) {
    light_cube_shader.use();
    light_cube_shader.setFloat3("spotLight.position",x,y,z);
}

void Drawer3D::change_light_color(float r, float g, float b) {
    light_cube_shader.use();
    light_cube_shader.setFloat3("spotLight.diffuse",  r,g,b);
}

void Drawer3D::change_light(const std::string& light_atrr_name,float value) {
    light_cube_shader.use();
    light_cube_shader.setFloat(light_atrr_name,value);
}

void Drawer3D::change_light(const std::string& light_atrr_name, math::vec3 value) {
    light_cube_shader.use();
    
    light_cube_shader.setFloat3(light_atrr_name,value.x,value.y,value.z);
}
