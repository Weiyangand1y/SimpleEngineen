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
    Texture(unsigned char* data,int w,int h,int c);
    Texture();
    ~Texture();
    void use();
    void use(int index);
    int get_id()const{return id;}
    float get_aspect_ratio()const{return (float)w/h;}
};
