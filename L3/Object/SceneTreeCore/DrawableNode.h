#pragma once
#include "Viewport.h"
#include "SceneNode.h"
#include "L1/Render/Drawer.h"

class DrawableNode : public SceneNode{
private:   
    
protected:
    Drawer* drawer;
public:
    void create_from_scene(Scene* scene)override;
    void after_process(float delta)override;
    virtual void draw();
};


