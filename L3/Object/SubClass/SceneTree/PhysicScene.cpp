#include "PhysicScene.h"

PhysicScene::PhysicScene(Application* p_app):Scene(p_app) {
    
}

void PhysicScene::init(float gravity_y, float gravity_x) {
    b2Vec2 gravity(gravity_x, gravity_y);
    physic_world=new b2World(gravity);
    add_handler("make_physic_object",[&](void* body_def)->void*{
        return physic_world->CreateBody((b2BodyDef*)body_def);
    });
}

void PhysicScene::run(float delta_time) {
    physic_world->Step(timeStep, velocityIterations, positionIterations);
    root_node->_process(delta_time);
    root_node->_after_process(delta_time);
}
