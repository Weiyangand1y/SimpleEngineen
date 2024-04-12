#include "PhysicNode.h"
#include "L3/Object/SceneTreeCore/Scene.h"
#include "L1/Debug/Log.h"
PhysicNode::PhysicNode() {
    
}

PhysicNode::PhysicNode(float sx, float sy) {
    m_scale={sx,sy};
}

void PhysicNode::_process(float delta_time) {
    m_position={body->GetPosition().x,body->GetPosition().y};
    m_rotation=body->GetAngle();
    Node::_process(delta_time);  
}

void PhysicNode::enter_scene(Scene* scene) {    
    SceneNode::enter_scene(scene);
    body =(b2Body*)scene->handle_requst("make_physic_object",&b2BodyDef());
    init_body();
}

// need to call after enter_scene
// I want to subclass to make it different
//   ... Make default ...
void PhysicNode::init_body() {    
    assert(body);
    set_body_type(body_type);
    body->SetTransform({m_position.x,m_position.y},m_rotation);
    math::vec2 v=m_size*m_scale;
    b2PolygonShape shape;
    shape.SetAsBox(v.x,v.y);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 0.1f;
    fixtureDef.friction =0.1f;
    fixtureDef.restitution = 0.5f; 
    body->CreateFixture(&fixtureDef);
}

void PhysicNode::set_transform(float px, float py, float r) {
    body->SetTransform({px,py},r);
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

void PhysicNode::set_body_type(BodyType p_body_type) {
    switch (p_body_type){
    case BodyType::DYNAMIC :
        body->SetType(b2_dynamicBody);
        break;
    case BodyType::STATIC :
        body->SetType(b2_staticBody);
    default:
        body->SetType(b2_kinematicBody);
        break;
    }
}

void PhysicNode::add_impulse(float x, float y) {
    body->ApplyLinearImpulse({x,y},body->GetWorldCenter(),true);
}

void PhysicNode::before_free() {
    SceneNode::before_free();
    scene->handle_requst("delete_physic_body",this);
}

void CircleNode::init_body() {
    assert(body);
    set_body_type(body_type);
    body->SetTransform({m_position.x,m_position.y},m_rotation);
    math::vec2 v=m_size*m_scale;
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
    Node::_process(delta_time);  
}

void CircleNode::set_circle_radius(float p_r) {
    auto current=body->GetFixtureList();
    current->GetShape()->m_radius=p_r;
}
