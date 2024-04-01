#pragma once
#include "L1/Object/Node.h"
#include "L1/Object/SignalObject.h"
class Scene;
class Viewport;
class SceneNode : public Node{
protected:
    Scene* scene;
    Viewport* viewport=nullptr;
public:
    SignalObject signal;
    virtual void create_from_scene(Scene* scene);
    virtual void add_child(SceneNode* node);
    void set_viewport(Viewport* p_viewport);
};