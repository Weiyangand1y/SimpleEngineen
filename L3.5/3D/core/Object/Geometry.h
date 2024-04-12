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
    void rotate(math::vec3 axis,float degree);
    void rotate_local(math::vec3 axis,float degree);
    math::vec3 to_vector(math::vec3 vec);
    float* get_matrix_ptr();
};
class Geometry{
public:
    Transform3D transform;
    virtual float* matrix_ptr()=0;
};
class Cube:public Geometry{
public:
    Cube();
    float* matrix_ptr();
};