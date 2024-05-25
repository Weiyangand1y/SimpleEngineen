#include "Node2D.h"
#include "L1/Lib/Math/Transform2D.h"
Node2D::Node2D() {
    set_name("@Node2D");
    class_name="Node2D";
}

math::mat4 Node2D::get_transform_matrix() {
    math::vec2 s2=m_scale*m_size;
    Transform2D t;
    t.translate_local(m_position);
    t.rotate_local_r(m_rotation);
    t.scale_local(s2);
    return t.model_matrix;
}

math::mat4 Node2D::get_transform_square_matrix() {   
    math::vec2 s2=m_scale*math::vec2(m_size.x>m_size.y?m_size.x:m_size.y);
    Transform2D t;
    t.translate_local(m_position);
    t.rotate_local_r(m_rotation);
    t.scale_local(s2);
    return t.model_matrix;
}

void Node2D::set_position(float x, float y) {
    m_position={x,y};
}

void Node2D::set_position_and_angle(float x, float y, float angle_r) {
    m_position={x,y};
    m_rotation=angle_r;
}

void Node2D::set_scale(float x, float y) {
    m_scale={x,y};
}

void Node2D::set_scale(float s) {
    m_scale={s,s};
}

void Node2D::set_who_to_follow(Node2D* p_to_follow) {
    who_to_follow=p_to_follow;
}

void Node2D::_process(float delta) {
    if(who_to_follow){
        m_position=who_to_follow->m_position+m_relative_pos;
        m_rotation=who_to_follow->m_rotation;
    }
    Node::_process(delta);
}
