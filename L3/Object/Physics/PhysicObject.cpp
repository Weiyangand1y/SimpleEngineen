#include "PhysicObject.h"
#include "L1/Debug/Log.h"
PhysicObject::PhysicObject(b2World* world) {
    init(world);
}

void PhysicObject::init(b2World* world) {
    body_def.position.Set(0.0f, 30.0f);
    body_def.type=b2_dynamicBody;
    body=world->CreateBody(&body_def);
    shape.SetAsBox(10.f,10.f);

    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);
}

float PhysicObject::get_position_x() {
    return body->GetPosition().x;
}

float PhysicObject::get_position_y() {
    return body->GetPosition().y;
}

PhysicObject::PhysicObject(){}