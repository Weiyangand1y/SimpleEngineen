#include "Shader.h"
#include "L1/Debug/CheckGL.h"
#include "L1/Debug/Log.h"
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
Shader::~Shader() {
    //GL_CALL(glDeleteProgram(id);)
}
void Shader::use() {
    GL_CALL(glUseProgram(id);)
}

int Shader::get_uniform_loc(const std::string& name){
    if (uniform_db.find(name) == uniform_db.end()) {
        GLint location = glGetUniformLocation(id, name.c_str());
        if (location == -1) {
            std::cout<<"Uniform [" + name + "] not found in shader."<<std::endl;
            assert(false);
        }
        uniform_db[name] = static_cast<int>(location);
    }
    return uniform_db[name];
}

void Shader::setBool(const std::string& name, bool value) {
    GL_CALL(glUniform1i(get_uniform_loc(name), (int)value));
}
void Shader::setInt(const std::string& name, int value) {
    GL_CALL(glUniform1i(get_uniform_loc(name), value));
}
void Shader::setFloat(const std::string& name, float value) {
    GL_CALL(glUniform1f(get_uniform_loc(name), value));
}

void Shader::setFloat4(const std::string& name,float v1,float v2,float v3,float v4) {
    GL_CALL(glUniform4f(get_uniform_loc(name), v1,v2,v3,v4));
}

void Shader::setFloat3(const std::string& name, float v1, float v2, float v3) {
    int loc=get_uniform_loc(name);
    GL_CALL(glUniform3f(loc, v1,v2,v3));
}

void Shader::setMat4(const std::string& name, const float* value) {
    GL_CALL(glUniformMatrix4fv(get_uniform_loc(name),1,GL_FALSE, value));
}

void Shader::compile_shader_from_string(const std::string& vertexCode,
                                        const std::string& fragmentCode) {
    unsigned int vertex, frag;
    vertex = compile_shader(GL_VERTEX_SHADER, vertexCode);
    frag = compile_shader(GL_FRAGMENT_SHADER, fragmentCode);
    attach_and_link_shader(vertex, frag);
}
