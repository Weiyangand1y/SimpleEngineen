#pragma once
#include <glad/glad.h>
#include <vector>
class BufferLayout
{    
private:
    unsigned int vbo_id;
    unsigned int vao;
    int stride=0;
    std::vector<int> elements;
    std::vector<int> offset_list;
public:
    BufferLayout();
    void add_vbo(unsigned int p_vbo_id);
    void add_float_layout(int count);
    void submit_float_layout();
    void bind();
    int get_stride()const{return stride;}
    unsigned int get_id()const{return vao;}
};

