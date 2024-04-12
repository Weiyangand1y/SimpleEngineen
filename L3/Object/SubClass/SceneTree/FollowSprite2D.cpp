#include "FollowSprite2D.h"
#include "L3/Object/SceneTreeCore/Viewport.h"
#include "L1/Debug/Log.h"
#include "L1/Lib/Math/Transform2D.h"
FollowSprite2D::FollowSprite2D() {
    signal.connect("click",[&](Info info){
        Transform2D t;
        t.model_matrix=viewport->get_transform_mat4()*get_transform();
        math::vec2 v2=t.to_vector({1.f,1.f});

        InfoWrapper iw(info);
        auto cx=iw.get_next_value<float>();
        auto cy=iw.get_next_value<float>();
        Transform2D t2;
        t2.model_matrix=inverse(get_transform())*inverse(viewport->get_transform_mat4());
        math::vec2 v4=t2.to_vector({cx,cy});
        // vec4 v3={cx,cy,0.f,1.f};
        // mat m1=inverse(viewport->get_transform_mat4());
        // math::mat4 m2=inverse(get_transform());
        // vec4 v4=m2*m1*v3;
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
