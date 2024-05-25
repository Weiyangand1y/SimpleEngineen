#include "PhysicScene.h"
#include "L1/Debug/Log.h"
class MyContactListener : public b2ContactListener {
    void BeginContact(b2Contact* contact) {
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();
        
        b2Body* bodyA = fixtureA->GetBody();
        b2Body* bodyB = fixtureB->GetBody();
        
        const char* a=(const char*)(bodyA->GetUserData().pointer);
        
        debug("collision a.name: {}\n",a);
    }
};
PhysicScene::PhysicScene(Application* p_app):Scene(p_app) {
    
}

void PhysicScene::init(float gravity_y, float gravity_x) {
    b2Vec2 gravity(gravity_x, gravity_y);
    physic_world=new b2World(gravity);
    physic_world->SetContactListener(new MyContactListener());
    add_handler("make_physic_object",[&](void* body_def){
        auto body=physic_world->CreateBody((b2BodyDef*)body_def);
        body->GetUserData().pointer=(uintptr_t)"123";
        return body;
    });
    add_handler("delete_physic_body",[&](void* body){
        physic_world->DestroyBody(static_cast<b2Body*>(body));
        return nullptr;
    });
}

void PhysicScene::run(float delta_time) {
    physic_world->Step(delta_time, velocityIterations, positionIterations);
    root_node->_process(delta_time);
    root_node->_after_process(delta_time);
}
