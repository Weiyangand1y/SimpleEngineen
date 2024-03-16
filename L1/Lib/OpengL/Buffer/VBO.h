#pragma once
#include <vector>
class VBO{
    unsigned int id;
public:
    VBO();
    VBO(std::vector<float>& vertex_data);
    int get_id()const{return id;}
    void bind();
};