#pragma once
#ifdef DEBUG
#include <glad/glad.h>
#define GL_CALL(X) \
        glGetError();\
        X;\
        check_and_print_error();
#else
#define GL_CALL(X) X;
#endif        
        
void check_and_print_error();