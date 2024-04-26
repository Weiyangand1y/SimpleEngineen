#include "Texture.h"
#include "../IO/imageLoader.h"
#include "L1/Debug/CheckGL.h"
#include "L1/Debug/TimeMeasure.h"
Texture::Texture(std::string filename,std::string* message){
    GL_CALL(glActiveTexture(GL_TEXTURE0);)
    GL_CALL(glGenTextures(1,&id);)
    GL_CALL(glBindTexture(GL_TEXTURE_2D,id);)
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  ) 
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);)
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);)
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);)

    int c;
    ImageLoader image_loader;
    unsigned char* data;
    MEASURE_TIME2(
        "load time",
        data=image_loader.loadImage(filename.c_str(),&w,&h,&c);
    );

    if (!data){
        if(message)*message=std::string("can't load image") ;
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
    //printf("(%d, %d, %d)\n",w,h,c);
}

Texture::Texture(unsigned char* data, int p_w, int p_h, int c) {
    w=p_w;
    h=p_h;
    GL_CALL(glActiveTexture(GL_TEXTURE0);)
    GL_CALL(glGenTextures(1,&id);)
    GL_CALL(glBindTexture(GL_TEXTURE_2D,id);)
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  ) 
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);)
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);)
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);)
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
    ImageLoader image_loader;
    image_loader.free_data(data);
}

Texture::Texture() {}

Texture::~Texture() {
    //GL_CALL (glDeleteTextures(1,&id));
}

void Texture::use() {
    GL_CALL(glBindTexture(GL_TEXTURE_2D,id);)
}
void Texture::use(int index) {
    glActiveTexture(GL_TEXTURE0+index);
    glBindTexture(GL_TEXTURE_2D,id);
}
