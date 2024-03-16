#pragma once
#include <unordered_map>
#include <string>
#include "L1/Lib/OpengL/Shader.h"
#include "L1/Lib/OpengL/Texture.h"
#include "L1/Lib/OpengL/Buffer/FrameBuffer.h"
class Render{
public:
    enum class VertexType{
        TRIANGLE,RECT,
        TEX_CUBE,COLOR_TRIANGLE,
        TEX_RECT
        };
    enum class ShaderType{
        VERY_SIMPLE, COLOR, RECT_TEXTURE,CAN_TRANSFORM,
        SCREEN
    };
private:
    std::unordered_map<std::string, FrameBuffer> frame_buffers;
    FrameBuffer* fb=nullptr;   
    void init();
    void init_vertex_db();
    void init_shader_db();
    void init_texture_db();
    std::unordered_map<VertexType,unsigned int> vertex_db;
    std::unordered_map<ShaderType,Shader> shader_db;
    std::unordered_map<std::string,Texture> texture_db;
    ShaderType current_shader_type;
public:
    Render();
    void use_vertex(VertexType vertex_type);
    
    void use_shader(ShaderType shader_type);
    Shader& get_shader();

    void use_texture(std::string id);
    Texture& get_texture(std::string id);

    void clear_color();
    void render();

    void start_framebuffer();
    void start_framebuffer(std::string frame_name);
    void end_framebuffer();
    int get_framebuffer_color_texture_id();
    int get_framebuffer_color_texture_id(std::string frame_name);
};