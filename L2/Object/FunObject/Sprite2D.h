#pragma once
#include "L1/Lib/Math/math.h"
class Sprite2D{
public:
    float x=0.f,y=0.f;
    float sx=0.4f,sy=0.4f;
    float rotation=0.f;
    void _move(float x,float y);
    void _rotate(float y);
    Sprite2D();
    mat4 get_transform_mat4();
};