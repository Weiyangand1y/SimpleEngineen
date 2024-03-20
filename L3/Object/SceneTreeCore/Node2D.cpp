#include "Node2D.h"

Node2D::Node2D() {}

mat4 Node2D::get_transform() {
    mat4 t(1.f);
    //!!!下面三个是右乘矩阵 
    t=translate(t,vec3(m_position,0.f));
    t=rotate(t,m_rotation,vec3(0.f,0.f,1.f));   
    vec2 s2=m_scale*m_size;
    t=scale(t,vec3(s2,1.f));
    return t;
}

void Node2D::set_position(float x, float y) {
    m_position={x,y};
}

void Node2D::set_position_and_angle(float x, float y, float angle) {
    m_position={x,y};
    m_rotation=angle;
}
