#include "Drawer.h"
#include "L1/Lib/Math/math.h"
#include <glad/glad.h>

#include "L1/Debug/CheckGL.h"
#include "L1/Lib/OpengL/Buffer/VBO.h"
#include "L1/Lib/OpengL/Buffer/BufferLayout.h"
#include "L1/Lib/Math/Transform2D.h"
Drawer::Drawer() {
    
}

void Drawer::draw_test() {
    
}

void Drawer::set_render(Render& p_renderer) {
    renderer=&p_renderer;
}

void Drawer::draw_triangle() {
    renderer->use_vertex(Render::VertexType::TRIANGLE);
    renderer->use_shader("very_simple");
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Drawer::draw_triangle(float x, float y, float sx, float sy) {
    Transform2D tf;
    tf.translate_local({x,y});
    tf.scale_local({sx,sy});
    renderer->use_vertex(Render::VertexType::TRIANGLE);
    Shader& shader=renderer->get_shader("can_transform");
    shader.use();
    shader.setMat4("transform",tf.get_matrix_ptr());
    glDrawArrays(GL_TRIANGLES, 0, 3);
}


void Drawer::draw_rect(){
    renderer->use_vertex(Render::VertexType::RECT);
    renderer->use_shader("very_simple");
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Drawer::draw_rect(const float* mat4_data) {
    renderer->use_vertex(Render::VertexType::RECT);
    Shader& shader=renderer->get_shader("can_transform");
    shader.use();
    shader.setMat4("transform",mat4_data);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Drawer::draw_rect(const float* mat4_data, float r,float g,float b,float a) {
    renderer->use_vertex(Render::VertexType::RECT);
    Shader& shader=renderer->get_shader("color_transform");
    shader.use();
    shader.setMat4("transform",mat4_data);
    shader.setFloat4("color",r,g,b,a);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Drawer::draw_texture(std::string id,float x,float y) {
    Transform2D t;
    t.translate_local({x,y});

    renderer->use_vertex(Render::VertexType::TEX_RECT);
    renderer->use_texture(id);

    Texture& texture=renderer->get_texture(id);
    Shader& shader=renderer->get_shader("rect_texture");
    shader.use();
    shader.setInt("texture1",0);
    shader.setMat4("transform",t.get_matrix_ptr());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Drawer::draw_texture(int id, const float* mat4_data) {
    renderer->use_vertex(Render::VertexType::TEX_RECT);
    renderer->use_texture(id);
    Shader& shader=renderer->get_shader("rect_texture");
    shader.use();
    shader.setInt("texture1",0);
    shader.setMat4("transform",mat4_data);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Drawer::draw_texture(std::string id,const float* mat4_data) {
    renderer->use_vertex(Render::VertexType::TEX_RECT);
    Texture& texture=renderer->get_texture(id);
    texture.use();
    Shader& shader=renderer->get_shader("rect_texture");
    shader.use();
    shader.setInt("texture1",0);
    shader.setMat4("transform",mat4_data);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Drawer::draw_texture(int texture_id, std::string shader_name) {
    math::mat4 t(1.f);
    renderer->use_vertex(Render::VertexType::TEX_RECT);

    Shader& shader=renderer->get_shader(shader_name);
    shader.use();
    glBindTexture(GL_TEXTURE_2D, texture_id);
    
    shader.setInt("texture1",0);
    shader.setMat4("transform",value_ptr(t));
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Drawer::draw_circle(const float* mat4_data,float r,float g,float b,float a) {
    renderer->use_vertex(Render::VertexType::CIRCLE);
    Shader& shader=renderer->get_shader("color_transform");
    shader.use();
    shader.setMat4("transform",mat4_data);
    shader.setFloat4("color",r,g,b,a);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 103);
}

void Drawer::draw_cube(const float* m,const float* v,const float* p,std::string key) {
    renderer->use_vertex(Render::VertexType::TEX_CUBE);
    Shader& s=renderer->get_shader("simple_cube");
    s.use();
    renderer->use_texture("p1",0);
    renderer->use_texture("Pippi_Carter",1);
    
    s.setInt("texture1",0);
    s.setInt("texture2",1);

    s.setMat4("view",v);
    s.setMat4("projection",p);
    s.setMat4("model", m);
}
