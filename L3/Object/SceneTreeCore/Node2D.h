#pragma once
#include "L3/Object/SceneTreeCore/SceneNode.h"
#include "L1/Lib/Math/math.h"
class Node2D: public SceneNode{
protected:
    
public:
    vec2 m_position=vec2(0.f);
    vec2 m_scale=vec2(1.f);
    vec2 m_size=vec2(1.f);
    float m_rotation=0.f;//radians
    Node2D();
    mat4 get_transform();
    mat4 get_transform2();
    void set_position(float x,float y);
    void set_position_and_angle(float x,float y,float angle);
};