#pragma once
#include "Node2D.h"
#include "L1/Render/Drawer.h"

class DrawableNode : public Node2D{
private:   
    bool visible=true;
protected:
    Drawer* drawer;
public:
    void create_from_scene(Scene* scene)override;
    void after_process(float delta)override;
    virtual void draw();
};


