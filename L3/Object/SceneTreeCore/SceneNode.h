#pragma once
#include "L1/Object/Node.h"

class Scene;
class Viewport;
class SceneNode : public Node{
protected:
    Scene* scene;
    Viewport* viewport=nullptr;
public:

    virtual void create_from_scene(Scene* scene);
    virtual void add_child(SceneNode* node);
    void set_viewport(Viewport* p_viewport);
};