#pragma once
#include "L3/Object/SceneTreeCore/Sprite2D.h"
class FollowSprite2D:public Sprite2D{
    Node2D* to_follow=nullptr;
    math::vec2 relative_position;
    float relative_rotation;
public:
    FollowSprite2D();
    void set_who_to_follow(Node2D* p_to_follow);
    void process(float delta)override;
};