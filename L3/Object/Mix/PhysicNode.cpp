#include "PhysicNode.h"
#include "L3/Object/SceneTreeCore/Scene.h"
#include "L1/Debug/Log.h"
PhysicNode::PhysicNode() {
    
}

void PhysicNode::_process(float delta_time) {
    m_position={body->GetPosition().x,body->GetPosition().y};
    m_rotation=body->GetAngle();
    Node::_process(delta_time);  
}

void PhysicNode::create_from_scene(Scene* scene) {    
    SceneNode::create_from_scene(scene);
    body =(b2Body*)scene->handle_requst("make_physic_object",&b2BodyDef());
    init_body();
}

// need to call after create_from_scene
// I want to subclass to make it different
void PhysicNode::init_body() {    
    assert(body);
    if(body_type==BodyType::DYNAMIC)body->SetType(b2_dynamicBody);
    else if(body_type==BodyType::DYNAMIC) body->SetType(b2_staticBody);
    else body->SetType(b2_kinematicBody);
    body->SetTransform({m_position.x,m_position.y},m_rotation);

    vec2 v=m_size*m_scale;
    b2PolygonShape shape;
    shape.SetAsBox(v.x,v.y);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 0.1f;
    fixtureDef.friction =0.1f;
    fixtureDef.restitution = 0.5f; 
    body->CreateFixture(&fixtureDef);
}

void PhysicNode::set_init_speed(float speed_x,float speed_y,float angle_speed) {
    assert(body);
    body->SetLinearVelocity(b2Vec2(speed_x,speed_y));
    body->SetAngularVelocity(angle_speed);
}

void PhysicNode::set_physic_material(float friction, float restitution,float density) {
    auto current=body->GetFixtureList();
    current->SetRestitution(restitution);
    current->SetFriction(friction);
    current->SetDensity(density);
    
}

void CircleNode::init_body() {
    assert(body);
    if(body_type==BodyType::DYNAMIC)body->SetType(b2_dynamicBody);
    else if(body_type==BodyType::DYNAMIC) body->SetType(b2_staticBody);
    else body->SetType(b2_kinematicBody);
    body->SetTransform({m_position.x,m_position.y},m_rotation);
    vec2 v=m_size*m_scale;
    b2CircleShape shape;
    shape.m_radius=v.y;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 0.1f;
    fixtureDef.friction =0.1f;
    fixtureDef.restitution = 0.5f; 
    body->CreateFixture(&fixtureDef);
}

void CircleNode::_process(float delta_time) {
    m_position={body->GetPosition().x,body->GetPosition().y};
    m_rotation=body->GetAngle();
    viewport->get_camera()->set_center_position(m_position);
    Node::_process(delta_time);  
}
