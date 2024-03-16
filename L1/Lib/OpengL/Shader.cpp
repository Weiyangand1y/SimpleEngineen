#include "Shader.h"
#include "L1/Debug/CheckGL.h"
int Shader::compile_shader(GLuint type, const std::string& code) {
    unsigned int shader_id = glCreateShader(type);
    const char* code_str = code.c_str();
    //std::cout << code_str << "\n";
    glShaderSource(shader_id, 1, &code_str, NULL);
    glCompileShader(shader_id);
    int success;
    char infoLog[256];
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader_id, 256, NULL, infoLog);
    }
    return shader_id;
}

void Shader::attach_and_link_shader(unsigned int vertex, unsigned int frag) {
    char infoLog[256];
    int success;

    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, frag);
    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(frag);
}

Shader& Shader::operator=(const Shader& other) {
    if (this != &other) {
        id=other.id;
        uniform_db=other.uniform_db;
    }
    return *this;
}

Shader::Shader() {}

Shader::Shader(const char* vs, const char* fs) {
    compile_shader_from_string(vs, fs);
}
Shader::Shader(const std::string& vs, const std::string& fs) {
    compile_shader_from_string(vs, fs);
}
void Shader::use() {
    glUseProgram(id);
}

void Shader::setBool(const std::string& name, bool value) const {
    GL_CALL(glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value));
}
void Shader::setInt(const std::string& name, int value) const {
    GL_CALL(glUniform1i(glGetUniformLocation(id, name.c_str()), value));
}
void Shader::setFloat(const std::string& name, float value) const {
    GL_CALL(glUniform1f(glGetUniformLocation(id, name.c_str()), value));
}

void Shader::setMat4(const std::string& name, const float* value) const {
    GL_CALL(glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()),1,GL_FALSE, value));
}

void Shader::compile_shader_from_string(const std::string& vertexCode,
                                        const std::string& fragmentCode) {
    unsigned int vertex, frag;
    vertex = compile_shader(GL_VERTEX_SHADER, vertexCode);
    frag = compile_shader(GL_FRAGMENT_SHADER, fragmentCode);
    attach_and_link_shader(vertex, frag);
}
