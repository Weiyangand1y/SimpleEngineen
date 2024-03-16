#include "Texture.h"
#include "../IO/imageLoader.h"
#include "L1/Debug/CheckGL.h"

Texture::Texture(std::string filename){
    GL_CALL(glActiveTexture(GL_TEXTURE0);)
    GL_CALL(glGenTextures(1,&id);)
    GL_CALL(glBindTexture(GL_TEXTURE_2D,id);)
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  ) 
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);)
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);)
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);)

    int w,h,c;
    ImageLoader image_loader;
    unsigned char* data=image_loader.loadImage(filename.c_str(),&w,&h,&c);
    if (!data){
        std::cout<<"can't load image"<<std::endl;
    }else{
        if(c==3){
            GL_CALL(glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,w,h,0,GL_RGB,GL_UNSIGNED_BYTE,data);)
        }else if (c==4){
            GL_CALL(glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,w,h,0,GL_RGBA,GL_UNSIGNED_BYTE,data);)
        }
               
        GL_CALL(glGenerateMipmap(GL_TEXTURE_2D);)
    }   
    image_loader.free_data(data);
    printf("(%d, %d, %d)\n",w,h,c);
}

Texture::Texture() {}

void Texture::use() {
    GL_CALL(glBindTexture(GL_TEXTURE_2D,id);)
}
void Texture::use(int index) {
    glActiveTexture(GL_TEXTURE0+index);
    glBindTexture(GL_TEXTURE_2D,id);
}