#pragma once
#ifdef DEBUG
#include <assert.h>
#include <glad/glad.h>
#define GL_CALL(X) \
        glGetError();\
        X;\
        if(!check_and_print_error())assert(false);
#else
#define GL_CALL(X) X;
#endif        
        
bool check_and_print_error();