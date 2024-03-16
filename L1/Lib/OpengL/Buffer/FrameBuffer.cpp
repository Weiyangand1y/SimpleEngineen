#include "FrameBuffer.h"
#include <glad/glad.h>
#include "L1/Debug/CheckGL.h"
#include <iostream>

FrameBuffer::FrameBuffer() {}

FrameBuffer::FrameBuffer(int pw, int ph) {
    set_size(pw,ph);
    create();
}

void FrameBuffer::create() {
    GL_CALL(glGenFramebuffers(1,&id));
    GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER,id));

    GL_CALL(glGenTextures(1,&color_texture_id));
    GL_CALL(glBindTexture(GL_TEXTURE_2D,color_texture_id));
    GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, 
                            GL_RGBA, GL_UNSIGNED_BYTE, nullptr));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GL_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,color_texture_id,0));
    

    GL_CALL(glGenTextures(1,&depth_texture_id));
    GL_CALL(glBindTexture(GL_TEXTURE_2D,depth_texture_id));
    GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, w, h, 0, 
                            GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr));
    GL_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,GL_TEXTURE_2D,depth_texture_id,0));


    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

    
    GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER,0));
}

void FrameBuffer::set_size(int pw, int ph) {
    w=pw;
    h=ph;
}


int FrameBuffer::get_id() {
    return id;
}

int FrameBuffer::get_color_texture_id() {
    return color_texture_id;
}

void FrameBuffer::bind() {
    GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER,id));
}

void FrameBuffer::unbind() {
    GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER,0));
}
