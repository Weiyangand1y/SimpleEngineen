#include "vbo.h"
#include "L1/Debug/CheckGL.h"
#include <glad/glad.h>
#include <vector>
#include <iostream>
VBO::VBO(){
    GL_CALL(glGenBuffers(1,&id));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER,id));
    std::vector<float> vertices={
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    }; 
    GL_CALL(glBufferData(GL_ARRAY_BUFFER,
                        vertices.size()*sizeof(float),vertices.data(),
                        GL_STATIC_DRAW));
    std::cout<<"vbo: "<<id<<"\tsize: "<<vertices.size()<<std::endl;
}

VBO::VBO(std::vector<float>& vertices_data) {
    GL_CALL(glGenBuffers(1,&id));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER,id));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER,
                        vertices_data.size()*sizeof(float),vertices_data.data(),
                        GL_STATIC_DRAW));
}

void VBO::bind() {
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER,id));
}
