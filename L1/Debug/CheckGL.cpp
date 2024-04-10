#include "CheckGL.h"
#ifdef DEBUG
#include <iostream>
#include <assert.h>
bool check_and_print_error(){
    
    GLenum error_code=glGetError();
    if(error_code!=GL_NO_ERROR){
        std::cout<<"** GL ERROR"<<std::endl;
        switch (error_code)
        {
        case GL_INVALID_ENUM:
            std::cout<<"GL_INVALID_ENUM"<<std::endl;
            break;
        case GL_INVALID_VALUE:
            std::cout<<"GL_INVALID_VALUE"<<std::endl;
            break;
        case GL_INVALID_OPERATION:
            std::cout<<"GL_INVALID_OPERATION"<<std::endl;
            break;
        default:
            std::cout<<"OTHER ERROR"<<std::endl;
            break;
        }
        return false;
    }
    return true;
    }
#endif   