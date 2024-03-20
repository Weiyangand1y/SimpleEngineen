#include "Sprite2D.h"
#include "Scene.h"
#include "L1/Debug/Log.h"

Sprite2D::Sprite2D(){
    set_name("@Sprite2D");
    m_position=vec2(5.f);
    m_scale=vec2(0.1f);
    m_rotation=0.f;
}

void Sprite2D::draw() {
    mat4 result=viewport->get_transform_mat4()*get_transform();
    drawer->draw_rect(value_ptr(result));
    drawer->draw_texture(texture_id,value_ptr(result));
}

void Sprite2D::set_texture(std::string name) {
    assert(scene);
    Render* r=scene->app->get_renderer();
    Texture& t=r->get_texture(name);
    texture_id = t .get_id();
    m_size={t.w,t.h};
    vec2 s2=m_scale*m_size;
    debug("ms: {}, {}\n",s2.x,s2.y);
}

void Sprite2D::process(float delta_time) {
    //m_position+=delta_time*1.f;
}

