#pragma once
#include <box2d/box2d.h>

class PhysicObject{
private:
    b2BodyDef body_def;
    b2Body* body;   
    b2PolygonShape shape;
    b2FixtureDef fixtureDef;
public:
    PhysicObject(b2World* world);
    PhysicObject();
    void init(b2World* world);
    float get_position_x();
    float get_position_y();
};

