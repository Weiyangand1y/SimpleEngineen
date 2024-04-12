#pragma once
#include "math.h"
class Transform2D{
public:    
    math::mat4 model_matrix;
    Transform2D();
    void translate(math::vec2 t);
    void translate_local(math::vec2 t);
    void scale(math::vec2 t);
    void scale_local(math::vec2 t);
    void rotate_r(float r);
    void rotate_local_r(float r);
    math::vec2 to_vector(math::vec2 vec);
    float* get_matrix_ptr();
};

