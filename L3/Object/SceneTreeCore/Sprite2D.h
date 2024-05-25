#pragma once
#include "DrawableNode.h"
#include <string>
class Sprite2D : public DrawableNode{
    unsigned int texture_id;
public:
    const char* texture_key;//用于序列化
    Sprite2D();
    void draw()override;
    void set_texture(const std::string& name);
};