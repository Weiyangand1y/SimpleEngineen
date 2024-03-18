#pragma once
#include "L1/Object/Node.h"
class Scene;
class SceneNode : public Node{
protected:
    Scene* scene;
public:
    virtual void create_from_scene(Scene* scene);
};