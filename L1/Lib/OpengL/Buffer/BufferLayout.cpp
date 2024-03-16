#include "BufferLayout.h"
#include <iostream>
#include "L1/Debug/CheckGL.h"
BufferLayout::BufferLayout(){
    glGenVertexArrays(1, &vao);
}
void BufferLayout::add_vbo(unsigned int p_vbo_id) {
    vbo_id=p_vbo_id;
}
void BufferLayout::add_float_layout(int count) {
    int size=sizeof(float)*count;
    if(elements.empty()){
        offset_list.push_back(0);        
    }
    offset_list.push_back(offset_list.back()+size);
    
    elements.push_back(count);
    stride+=size;
}
void BufferLayout::submit_float_layout(){
    glBindVertexArray(vao);
    for (int index = 0; index < elements.size(); index++){
        glVertexAttribPointer(
                    index, elements[index], GL_FLOAT, GL_FALSE, stride,
                    (void*)(offset_list[index])
        );
    glEnableVertexAttribArray(index);
    //std::cout << index << "," << stride << "," << elements[index] << "," << offset_list[index] << std::endl;
    }    
}

void BufferLayout::bind() {
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER,vbo_id));
    GL_CALL(glBindVertexArray(vao));
}
