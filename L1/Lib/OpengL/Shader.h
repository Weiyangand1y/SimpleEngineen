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

public:
    unsigned int id;
    Shader& operator=(const Shader& other);
    Shader();
    Shader(const char* vs, const char* fs);
    Shader(const std::string& vs, const std::string& fs);
    std::unordered_map<std::string, int> uniform_db;
    void use();

    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMat4(const std::string& name, const float* value) const;
    void compile_shader_from_string(const std::string& vertexCode,
                                    const std::string& fragmentCode);
};

#endif