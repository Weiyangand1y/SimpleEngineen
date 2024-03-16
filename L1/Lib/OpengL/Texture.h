#pragma once
#include <glad/glad.h>
#include <iostream>
#include <string>

class Texture {
private:
    unsigned int id;
public:
    Texture(std::string filename);
    Texture();
    void use();
    void use(int index);
    int get_id(){return id;}
};
