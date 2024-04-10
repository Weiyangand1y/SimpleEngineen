#pragma once
#include <string>
#include <vector>
constexpr int MATRIX_SIZE=64;
class UBO{
    unsigned int id;
    std::vector<int> offset;   
    std::vector<int> elements;
public:
    UBO(int size);
    UBO();
    void init(int size);
    int get_id()const{return id;}
    void bind_shader_uniform(unsigned int shader_id,const std::string& block_name,int index=0);
    void update(int size,int offset,void* data);
    void wrap_update(int index,void* data);
    void bind();
    //第n个元素起始点相对于第n-1元素的起始点的偏移和第n个元素的大小
    void add_layout(int size,int p_offset=-1);
};