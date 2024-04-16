#pragma once
#include <glad/glad.h>
#include <iostream>
#include <string>

class Texture {
private:
    unsigned int id;
public:
    int w,h;
    Texture(std::string filename,std::string* message=nullptr);
    Texture();
    ~Texture();
    void use();
    void use(int index);
    int get_id(){return id;}
};
