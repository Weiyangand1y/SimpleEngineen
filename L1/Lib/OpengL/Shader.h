#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
class Shader {
private:
    int compile_shader(GLuint type, const std::string& code);
    void attach_and_link_shader(unsigned int vertex, unsigned int frag);
    int get_uniform_loc(const std::string& name);
    std::unordered_map<std::string, int> uniform_db;
public:
    unsigned int id;
    Shader& operator=(const Shader& other);
    Shader();
    Shader(const char* vs, const char* fs);
    Shader(const std::string& vs, const std::string& fs);
    ~Shader();
    
    void use();

    void setBool(const std::string& name, bool value) ;
    void setInt(const std::string& name, int value) ;
    void setFloat(const std::string& name, float value) ;
    void setFloat4(const std::string& name, float v1,float v2,float v3,float v4) ;
    void setMat4(const std::string& name, const float* value) ;
    void compile_shader_from_string(const std::string& vertexCode,
                                    const std::string& fragmentCode);
};

#endif