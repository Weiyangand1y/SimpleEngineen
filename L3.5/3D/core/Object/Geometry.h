#pragma once
#include "L1/Lib/Math/math.h"
class Transform3D{
public:    
    math::mat4 model_matrix;
    Transform3D();
    void translate(math::vec3 t);
    void translate_local(math::vec3 t);
    void scale(math::vec3 t);
    void scale_local(math::vec3 t);
    void rotate(math::vec3 axis,float angle);
    void rotate_local(math::vec3 axis,float angle);
    float* get_matrix_ptr();
};
class Cube{
public:
    Transform3D t3d;
    Cube();
    float* matrix_ptr();
};