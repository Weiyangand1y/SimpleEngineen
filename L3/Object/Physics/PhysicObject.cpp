#include "PhysicObject.h"
#include "L1/Debug/Log.h"
PhysicObject::PhysicObject(BodyType p_body_type) {
    body_type=p_body_type;
}

void PhysicObject::init(b2World* world) {
    body_def.position.Set(init_info.px,init_info.py);
    body_def.angle=init_info.angle;
    if(body_type==BodyType::DYNAMIC)body_def.type=b2_dynamicBody;
    else body_def.type=b2_staticBody;

    body=world->CreateBody(&body_def);
    shape.SetAsBox(init_info.sx,init_info.sy);
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.1f;
    fixtureDef.restitution = 1.0f; // 设置弹性为 0.5
    body->CreateFixture(&fixtureDef);
}


PhysicObject::PhysicObject(){}

void PhysicObject::update(){
    update_callback(body->GetPosition().x,body->GetPosition().y,body->GetAngle());
}

void PhysicObject::set_init_speed(float x,float y) {
    body->SetLinearVelocity(b2Vec2(x,y));
    body->SetAngularVelocity(0.3f);
}
