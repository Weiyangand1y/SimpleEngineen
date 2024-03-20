#pragma once
#include "L3/Object/SceneTreeCore/DrawableNode.h"
class RectDraw : public DrawableNode{
public:
    RectDraw(){}
    void draw()override{
        mat4 result=viewport->get_transform_mat4()*get_transform();
        drawer->draw_rect(value_ptr(result),0.3f,0.7f,0.9f,0.3f);
    }
};