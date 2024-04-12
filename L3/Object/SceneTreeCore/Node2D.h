#pragma once
#include "L3/Object/SceneTreeCore/SceneNode.h"
#include "L1/Lib/Math/math.h"
class Node2D: public SceneNode{
    Node2D* who_to_follow=nullptr;
protected:
    
public:
    math::vec2 m_relative_pos=math::vec2(0.f);
    math::vec2 m_position=math::vec2(0.f);
    math::vec2 m_scale=math::vec2(1.f);
    math::vec2 m_size=math::vec2(1.f);
    float m_rotation=0.f;//radians

    Node2D();
    math::mat4 get_transform();
    math::mat4 get_transform2();
    void set_position(float x,float y);
    void set_position_and_angle(float x,float y,float angle);
    void set_scale(float x,float y);
    void set_scale(float s);
    void set_who_to_follow(Node2D* p_to_follow);
    void _process(float delta)override;
};