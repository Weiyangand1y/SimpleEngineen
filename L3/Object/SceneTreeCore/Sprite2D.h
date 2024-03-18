#include "DrawableNode.h"
#include "L1/Lib/Math/math.h"
#include <string>
class Sprite2D : public DrawableNode{
    vec2 m_position;
    vec2 m_scale;
    float m_rotation;
    unsigned int texture_id;
public:
    Sprite2D();
    mat4 get_transform();
    void draw()override;
    void set_texture(std::string name);
    void process(float delta_time)override;
};