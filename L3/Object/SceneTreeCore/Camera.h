#pragma once
#include "L1/Lib/Math/math.h"
class Camera{
    vec2 center_position;
    vec2 half_wh;
public:
    mat4& get_transform_mat4();
};