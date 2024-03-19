#include <box2d/box2d.h>
#include "PhysicObject.h"
class PhysicWorld{
private:
    b2World* world;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    float timeStep = 1.0f / 60.0f;
public:
    PhysicWorld();
    void create_object(PhysicObject* obj);
    void run();
};


