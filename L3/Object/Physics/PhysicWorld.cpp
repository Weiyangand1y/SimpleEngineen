#include "PhysicWorld.h"
#include "L1/Debug/Log.h"

int GetBodyCount(b2World* world) {
    int count = 0;
    for (b2Body* body = world->GetBodyList(); body; body = body->GetNext()) {
        count++;
    }
    return count;
}

PhysicWorld::PhysicWorld() {
    b2Vec2 gravity(0.0f, -1.0f);
    world=new b2World(gravity);
}

void PhysicWorld::create_object(PhysicObject* obj) {
    obj->init(world);
}

void PhysicWorld::run() {
    world->Step(timeStep, velocityIterations, positionIterations);
}

