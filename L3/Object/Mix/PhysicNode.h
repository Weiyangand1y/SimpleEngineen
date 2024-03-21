#pragma once
#include "L3/Object/SceneTreeCore/DrawableNode.h"
#include "box2d/box2d.h"
#include "L1/Lib/Math/math.h"
//之所以是DrawableNode，考虑到可以用纯色矩形
class PhysicNode : public Node2D{
public:
    enum class BodyType {STATIC, DYNAMIC};
private:
       
protected:
    b2Body* body;
public:
    BodyType body_type=BodyType::DYNAMIC;  
    PhysicNode();
    void _process(float delta_time)override;
    void create_from_scene(Scene* scene)override;
    virtual void init_body();
    void set_init_speed(float speed_x,float speed_y,float angle_speed=0.f);
    void set_physic_material(float friction,float restitution,float density=1.f);
};

class CircleNode : public PhysicNode{
public:
    void init_body()override;
    void _process(float delta_time)override;
};