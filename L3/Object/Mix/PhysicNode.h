#pragma once
#include "L3/Object/SceneTreeCore/DrawableNode.h"
#include "box2d/box2d.h"
#include "L1/Lib/Math/math.h"

class PhysicNode : public Node2D{
public:
    enum class BodyType {STATIC, DYNAMIC};
private:
       
protected:
    b2Body* body;
public:
    BodyType body_type=BodyType::DYNAMIC;  
    PhysicNode();
    PhysicNode(float sx,float sy);
    void _process(float delta_time)override;
    void enter_scene(Scene* scene)override;
    virtual void init_body();
    void set_transform(float px,float py,float r=0.f);
    void set_init_speed(float speed_x,float speed_y,float angle_speed=0.f);
    void set_physic_material(float friction,float restitution,float density=1.f);
    void set_body_type(BodyType p_body_type);

    void add_impulse(float x,float y);
};

class CircleNode : public PhysicNode{
public:
    void init_body()override;
    void _process(float delta_time)override;
    void set_circle_radius(float p_r);
};