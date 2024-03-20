#pragma once
#include "DrawableNode.h"
#include "L1/Lib/Math/math.h"
#include <string>
class Sprite2D : public DrawableNode{
    unsigned int texture_id;
public:
    Sprite2D();
    void draw()override;
    void set_texture(std::string name);
    void process(float delta_time)override;
};