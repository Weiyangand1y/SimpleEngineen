#include "Drawer.h"
#include "L1/Lib/Math/math.h"
#include <glad/glad.h>

Drawer::Drawer() {
    
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
    mat4 t(1.f);
    translate(t,vec3(x,y,0.0));
    scale(t,vec3(sx,sy,0));
    renderer->use_vertex(Render::VertexType::TRIANGLE);
    renderer->use_shader("can_transform");
    Shader& shader=renderer->get_shader("can_transform");
    shader.setMat4("transform",value_ptr(t));
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
    mat4 t(1.f);
    translate(t,vec3(x,y,0.0));

    renderer->use_vertex(Render::VertexType::TEX_RECT);
    renderer->use_texture(id);

    Texture& texture=renderer->get_texture(id);
    Shader& shader=renderer->get_shader("rect_texture");
    shader.use();
    shader.setInt("texture1",0);
    shader.setMat4("transform",value_ptr(t));
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Drawer::draw_texture(int id, const float* mat4_data) {
    renderer->use_vertex(Render::VertexType::TEX_RECT);
    renderer->use_texture(id);
    Shader& shader=renderer->get_shader("rect_texture");
    shader.use();
    shader.setInt("texture1",0);
    shader.setMat4("transform",mat4_data);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Drawer::draw_texture(std::string id,const float* mat4_data) {
    renderer->use_vertex(Render::VertexType::TEX_RECT);
    Texture& texture=renderer->get_texture(id);
    texture.use();
    Shader& shader=renderer->get_shader("rect_texture");
    shader.use();
    shader.setInt("texture1",0);
    shader.setMat4("transform",mat4_data);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Drawer::draw_texture(int texture_id, std::string shader_name) {
    mat4 t(1.f);
    renderer->use_vertex(Render::VertexType::TEX_RECT);

    Shader& shader=renderer->get_shader(shader_name);
    shader.use();
    glBindTexture(GL_TEXTURE_2D, texture_id);
    
    shader.setInt("texture1",0);
    shader.setMat4("transform",value_ptr(t));
    glDrawArrays(GL_TRIANGLES, 0, 6);
}


