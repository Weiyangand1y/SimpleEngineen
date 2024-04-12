#include "Sprite2D.h"
#include "Scene.h"
#include "L1/Debug/Log.h"

Sprite2D::Sprite2D(){
    set_name("@Sprite2D");
    m_position=vec2(0.f);
    m_scale=vec2(0.1f);
    m_rotation=0.f;
}

void Sprite2D::draw() {
    math::mat4 result=viewport->get_transform_mat4()*get_transform();
    math::mat4 m2=viewport->get_transform_mat4()*get_transform2();
    drawer->draw_rect(value_ptr(result));


    drawer->draw_circle(value_ptr(m2),0.9f,0.4f,0.8f,0.4f);
    drawer->draw_texture(texture_id,value_ptr(result));
}

void Sprite2D::set_texture(std::string name) {
    assert(scene);
    Render* r=scene->app->get_renderer();
    Texture& t=r->get_texture(name);
    texture_id = t.get_id();
    m_size={t.w,t.h};
    vec2 s2=m_scale*m_size;
    debug("sprite[{}] total size: {:.2f}, {:.2f}\n",name,s2.x,s2.y);
}

void Sprite2D::process(float delta_time) {
    //m_position+=delta_time*1.f;
    vec4 p1=vec4(1.f,1.f,0.f,1.f);
    math::mat4 result=viewport->get_transform_mat4()*get_transform();
    p1=result*p1;
    //debug(">> {:.2f}, {:.2f}, {:.2f}, {:.2f}\n",p1.x,p1.y,p1.z,p1.w);
}

