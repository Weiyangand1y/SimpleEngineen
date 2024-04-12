#include "Node2D.h"
#include "L1/Lib/Math/Transform2D.h"
Node2D::Node2D() {}

math::mat4 Node2D::get_transform() {
    math::vec2 s2=m_scale*m_size;
    Transform2D tf;
    tf.translate_local(m_position);
    tf.rotate_local_r(m_rotation);
    tf.scale_local(s2);
    return tf.model_matrix;
}

//
math::mat4 Node2D::get_transform2() {   
    math::vec2 s2=m_scale*math::vec2(m_size.y);
    Transform2D tf;
    tf.translate_local(m_position);
    tf.rotate_local_r(m_rotation);
    tf.scale_local(s2);
    return tf.model_matrix;
}

void Node2D::set_position(float x, float y) {
    m_position={x,y};
}

void Node2D::set_position_and_angle(float x, float y, float angle) {
    m_position={x,y};
    m_rotation=angle;
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
