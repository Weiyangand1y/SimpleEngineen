#include "FollowSprite2D.h"

FollowSprite2D::FollowSprite2D() {}

void FollowSprite2D::set_who_to_follow(Node2D* p_to_follow) {
    to_follow=p_to_follow;
}

void FollowSprite2D::process(float delta) {
    assert(to_follow);
    m_position=to_follow->m_position;
    m_rotation=to_follow->m_rotation;
}
