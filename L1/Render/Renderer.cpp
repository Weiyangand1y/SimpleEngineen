#include "Renderer.h"
#include "L1/Lib/OpengL/Buffer/VBO.h"
#include "L1/Lib/OpengL/Buffer/BufferLayout.h"
#include "L1/Debug/CheckGL.h"
#include "L1/Lib/IO/textLoader.h"
#include "L1/App/Config.h"
Render::Render() {
    init();
    glClearColor(0.94f, 0.84f, 0.44f, 1.0f);
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



void Render::init() {
    init_vertex_db();
    init_shader_db();
    init_texture_db();
    frame_buffers["f1"]=FrameBuffer(800,800);
    fb=&frame_buffers["f1"];
    
}

void Render::init_shader_db() {
    std::string base_path=Config::getInstance().get("shader_base_path");
    std::string very_simple_v=loadTextFile(base_path+"very_simple.vert");
    std::string very_simple_f=loadTextFile(base_path+"very_simple.frag");
    std::string simple_texture_v=loadTextFile(base_path+"simple_texture.vert");
    std::string simple_texture_f=loadTextFile(base_path+"simple_texture.frag");

    Shader very_simple_shader(very_simple_v,very_simple_f);
    std::string can_transform_v=loadTextFile(base_path+"transform.vert");
    shader_db[ShaderType::VERY_SIMPLE]=very_simple_shader;
    shader_db[ShaderType::CAN_TRANSFORM]=Shader(can_transform_v,very_simple_f);
    shader_db[ShaderType::RECT_TEXTURE]=Shader(simple_texture_v,simple_texture_f);
    std::string screen_texture_f=loadTextFile(base_path+"screen_texture.frag");
    shader_db[ShaderType::SCREEN]=Shader(simple_texture_v,screen_texture_f);
}

void Render::init_texture_db() {
    std::string base_path=Config::getInstance().get("texture_base_path");
    texture_db["Claudette_Huy"]=Texture(base_path+"character/Claudette_Huy.png");    
    texture_db["Maki_Rollo"]=Texture(base_path+"character/Maki_Rollo.png");
    texture_db["Pippi_Carter"]=Texture(base_path+"character/Pippi_Carter.png");
}

void Render::use_vertex(VertexType vertex_type) {
    unsigned int vao_id=vertex_db[vertex_type];
    glBindVertexArray(vao_id);
}

void Render::use_shader(ShaderType shader_type) {
    shader_db[shader_type].use();
    current_shader_type=shader_type;
}

Shader& Render::get_shader() {
    return shader_db[current_shader_type];
}

void Render::use_texture(std::string id) {
    texture_db[id].use();
}

Texture& Render::get_texture(std::string id) {
    return texture_db[id];
}


void Render::clear_color() {
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT));  
}

void Render::render() {
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT));     
    glDrawArrays(GL_TRIANGLES, 0, 6);
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