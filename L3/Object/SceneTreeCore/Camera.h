#pragma once
#include "L1/Lib/Math/math.h"
class Camera{
    math::vec2 center_position;
    float top,bottom,left,right;
    math::mat4 view_projection_matrix;
    void update_mat();
public:
    math::mat4& get_view_projection_matrix();
    Camera();
    Camera(math::vec2 p_center_position, math::vec2 p_half_wh);
    void set_center_position(math::vec2 p_center_position);
    void set_half_wh(math::vec2 p_half_wh);
};