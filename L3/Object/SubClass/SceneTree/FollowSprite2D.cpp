#include "FollowSprite2D.h"
#include "L3/Object/SceneTreeCore/Viewport.h"
#include "L1/Debug/Log.h"
#include "L1/Lib/Math/Transform2D.h"
FollowSprite2D::FollowSprite2D() {
    signal.connect("click",[&](Info info){
        //物体的位置
        Transform2D t;
        t.model_matrix=viewport->get_view_projection_matrix()*get_transform_matrix();
        math::vec2 v2=t.to_vector({1.f,1.f});

        InfoWrapper iw(info);
        float ceneter_x,center_y;
        iw.next_value(ceneter_x).next_value(center_y);
        Transform2D t2;
        t2.model_matrix=glm::inverse(get_transform_matrix())*glm::inverse(viewport->get_view_projection_matrix());
        math::vec2 v4=t2.to_vector({ceneter_x,center_y});
        //经过转换，如果在矩形区域内，应该在-1~1之间
        if(abs(v4.x)<1.f && abs(v4.y)<1.f)Logger::log(1,"***on Click");
        Logger::log(0,"follow sprite loc: {:.4f} {:.4f} <<< {} {}",v2.x,v2.y,v4.x,v4.y);
    });
}

void FollowSprite2D::set_who_to_follow(Node2D* p_to_follow) {
    to_follow=p_to_follow;
}

void FollowSprite2D::process(float delta) {
    assert(to_follow);
    m_position=to_follow->m_position;
    m_rotation=to_follow->m_rotation;
  
}
