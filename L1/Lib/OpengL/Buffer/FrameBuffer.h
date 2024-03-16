#pragma once
class FrameBuffer{
    unsigned int id;
    unsigned int color_texture_id,depth_texture_id;
    int w,h;
public:
    FrameBuffer();
    FrameBuffer(int pw,int ph);
    void create();
    void set_size(int pw,int ph);
    int get_id();
    int get_color_texture_id();
    void bind();
    void unbind();
};