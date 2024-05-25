#include "PhysicWorld.h"
#include "L1/Debug/Log.h"


class MyContactListener : public b2ContactListener {
    void BeginContact(b2Contact* contact) {
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();
        
        b2Body* bodyA = fixtureA->GetBody();
        b2Body* bodyB = fixtureB->GetBody();
        
        const char* a=(const char*)(bodyA->GetUserData().pointer);
        
        debug("a.name: {}\n",a);
    }
};


int GetBodyCount(b2World* world) {
    int count = 0;
    for (b2Body* body = world->GetBodyList(); body; body = body->GetNext()) {
        count++;
    }
    return count;
}

PhysicWorld::PhysicWorld() {
    b2Vec2 gravity(0.0f, -10.0f);
    world=new b2World(gravity);
}

void PhysicWorld::register_object(PhysicObject* obj) {
    obj->init(world);
}

void PhysicWorld::run() {
    world->Step(timeStep, velocityIterations, positionIterations);
}

