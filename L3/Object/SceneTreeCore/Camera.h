#pragma once
#include "L1/Lib/Math/math.h"
class Camera{
    vec2 center_position;
    float top,bottom,left,right;
    mat4 transform_mat4;
    void update_mat();
public:
    mat4& get_transform_mat4();
    Camera();
    Camera(vec2 p_center_position, vec2 p_half_wh);
    void set_center_position(vec2 p_center_position);
    void set_half_wh(vec2 p_half_wh);
};