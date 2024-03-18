#include "Renderer.h"
#include "L1/Lib/OpengL/Buffer/VBO.h"
#include "L1/Lib/OpengL/Buffer/BufferLayout.h"
#include "L1/Debug/CheckGL.h"
#include "L1/Lib/IO/textLoader.h"
#include "L1/App/Config.h"
Render::Render() {}

void Render::init() {
    glClearColor(0.94f, 0.84f, 0.44f, 1.0f);

    init_vertex_db();
    shader_db.init();
    texture_db.init();

    auto [w,h]=Config::getInstance().get_windows_size();
    frame_buffers["f1"]=FrameBuffer(w,h);
    fb=&frame_buffers["f1"];   
}


void Render::start_framebuffer() {
    fb->bind();
}

void Render::start_framebuffer(std::string frame_name) {
    if(frame_buffers.find(frame_name)==frame_buffers.end()){
        frame_buffers[frame_name]=FrameBuffer(800,800);        
    }
    fb=&frame_buffers[frame_name];
    fb->bind();
}

void Render::end_framebuffer() {
    fb->unbind();
}

int Render::get_framebuffer_color_texture_id() {
    return fb->get_color_texture_id();
}

int Render::get_framebuffer_color_texture_id(std::string frame_name) {
    return frame_buffers[frame_name].get_color_texture_id();
}


void Render::use_vertex(VertexType vertex_type) {
    unsigned int vao_id=vertex_db[vertex_type];
    glBindVertexArray(vao_id);
}

void Render::use_shader(std::string shader_name) {
    shader_db.get_shader(shader_name).use();
}

Shader& Render::get_shader(std::string shader_name) {
    return shader_db.get_shader(shader_name);
}

ShaderDB& Render::get_shader_db() {
    return shader_db;
}

void Render::use_texture(std::string name) {
    texture_db.get_texture(name).use();
}

Texture& Render::get_texture(std::string name) {
    return texture_db.get_texture(name);
}

TextureDB& Render::get_texture_db() {
    return texture_db;
}

void Render::clear_color() {
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT));  
}


void Render::init_vertex_db() {
    //triangle
    std::vector<float> triangle_vertices={
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    };
    VBO triangle_vbo(triangle_vertices);
    BufferLayout triangle_bufferLayout;
    triangle_bufferLayout.add_float_layout(3);
    triangle_bufferLayout.add_vbo(triangle_vbo.get_id());
    triangle_bufferLayout.submit_float_layout();
    vertex_db.emplace(VertexType::TRIANGLE,triangle_bufferLayout.get_id());
    //color_triangle
    std::vector<float> color_triangle_vertices = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
    };
    VBO color_triangle_vbo(color_triangle_vertices);
    BufferLayout color_triangle_bufferLayout;
    color_triangle_bufferLayout.add_float_layout(3);
    color_triangle_bufferLayout.add_float_layout(3);
    color_triangle_bufferLayout.add_vbo(color_triangle_vbo.get_id());
    color_triangle_bufferLayout.submit_float_layout();
    vertex_db.emplace(VertexType::COLOR_TRIANGLE,color_triangle_bufferLayout.get_id());
    //rect
    std::vector<float> rect_vertices = {
        // positions   
        -0.5f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f, 
         0.5f, -0.5f, 0.0f, 

        -0.5f,  0.5f, 0.0f, 
         0.5f, -0.5f, 0.0f, 
         0.5f,  0.5f, 0.0f, 
    };
    VBO rect_vbo(rect_vertices);
    BufferLayout rect_bufferLayout;
    rect_bufferLayout.add_float_layout(3);
    rect_bufferLayout.add_vbo(rect_vbo.get_id());
    rect_bufferLayout.submit_float_layout();
    vertex_db.emplace(VertexType::RECT,rect_bufferLayout.get_id());
    //texture rect
    std::vector<float> texture_rect_vertices={
        // positions         // texture coords
        0.5f,  0.5f, 0.0f,  1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, // bottom left

        0.5f,  0.5f, 0.0f,  1.0f, 1.0f, // top right
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f  // top left 
    };
    VBO texture_rect_vbo(texture_rect_vertices);
    BufferLayout texture_rect_bufferLayout;
    texture_rect_bufferLayout.add_float_layout(3);
    texture_rect_bufferLayout.add_float_layout(2);
    texture_rect_bufferLayout.add_vbo(texture_rect_vbo.get_id());
    texture_rect_bufferLayout.submit_float_layout();
    vertex_db.emplace(VertexType::TEX_RECT,texture_rect_bufferLayout.get_id());

    //cube
    std::vector<float> cube_vertices = {
        // positions          // texture Coords
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

}