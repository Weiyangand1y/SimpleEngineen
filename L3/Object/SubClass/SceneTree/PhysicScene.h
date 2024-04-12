#include "L3/Object/SceneTreeCore/Scene.h"
#include "L3/Object/Physics/PhysicWorld.h"
#include "L3/Object/Physics/PhysicObject.h"
class PhysicScene : public Scene{
b2World* physic_world;
int32 velocityIterations = 6;
int32 positionIterations = 2;
float timeStep = 1.0f / 144.0f;
public:
    PhysicScene(Application* p_app);
    void init(float gravity_y=-10.f,float gravity_x=0.f);
    void run(float delta_time)override;
};