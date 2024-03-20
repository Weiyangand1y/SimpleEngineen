#pragma once
#include <unordered_map>
#include <string>
#include "L1/Lib/OpengL/Shader.h"
#include "L1/Lib/OpengL/Texture.h"
#include "L1/Lib/OpengL/Buffer/FrameBuffer.h"
#include "L1/ResourceManger/TextureDB.h"
#include "L1/ResourceManger/ShaderDB.h"

class Render{
public:
    enum class VertexType{
        TRIANGLE,RECT,
        TEX_CUBE,COLOR_TRIANGLE,
        TEX_RECT,CIRCLE
        };
private:
    std::unordered_map<std::string, FrameBuffer> frame_buffers;
    FrameBuffer* fb=nullptr;   
    void init_vertex_db();

    std::unordered_map<VertexType,unsigned int> vertex_db;

    TextureDB texture_db;
    ShaderDB shader_db;

public:
    Render();
    void init();
    void use_vertex(VertexType vertex_type);
    
    void use_shader(std::string shader_name);
    Shader& get_shader(std::string shader_name);
    ShaderDB& get_shader_db();

    void use_texture(std::string name);
    void use_texture(int texture_id);
    Texture& get_texture(std::string name);
    TextureDB& get_texture_db();

    void clear_color();

    void start_framebuffer();
    void start_framebuffer(std::string frame_name);
    void end_framebuffer();
    int get_framebuffer_color_texture_id();
    int get_framebuffer_color_texture_id(std::string frame_name);
};