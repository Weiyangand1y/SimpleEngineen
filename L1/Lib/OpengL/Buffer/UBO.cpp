#include "UBO.h"
#include "L1/Debug/CheckGL.h"
#include "L1/Debug/Log.h"
#include <glad/glad.h>

//If two matrix, size of *2
UBO::UBO(int size) {
    init(size);
}

UBO::UBO() {}

void UBO::init(int size) {
    GL_CALL(glGenBuffers(1,&id);)
    GL_CALL(glBindBuffer(GL_UNIFORM_BUFFER,id);)
    GL_CALL(glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_STATIC_DRAW);) 
    GL_CALL(glBindBufferRange(GL_UNIFORM_BUFFER, 0, id, 0, size);)
    GL_CALL(glBindBuffer(GL_UNIFORM_BUFFER, 0);)
    offset.push_back(0);
}

void UBO::bind_shader_uniform(unsigned int shader_id, const std::string& block_name,int index) {
    bind();
    GLint uniformBlockIndex = glGetUniformBlockIndex(shader_id, block_name.c_str());
    GL_CALL(glUniformBlockBinding(shader_id, uniformBlockIndex, index); )
}

void UBO::update(int size,int offset,void* data) {
    GL_CALL(glBindBuffer(GL_UNIFORM_BUFFER, id);)
    GL_CALL(glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);)
    GL_CALL(glBindBuffer(GL_UNIFORM_BUFFER, 0);)
}

void UBO::wrap_update(int index, void* data) {
    GL_CALL(glBindBuffer(GL_UNIFORM_BUFFER, id);)
    Logger::log(1,"*******{},  {},  {}",index, offset[index], elements[index]);
    GL_CALL(glBufferSubData(GL_UNIFORM_BUFFER, offset[index], elements[index], data);)
    GL_CALL(glBindBuffer(GL_UNIFORM_BUFFER, 0);)
}

void UBO::bind() {
    GL_CALL(glBindBuffer(GL_UNIFORM_BUFFER,id);)
}

void UBO::add_layout(int size,int p_offset) {
    if(p_offset==-1)p_offset=size;
    offset.push_back(offset.back()+p_offset);
    elements.push_back(size);
}
