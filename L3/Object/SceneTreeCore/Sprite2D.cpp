#include "Sprite2D.h"
#include "Scene.h"
#include "L1/Debug/Log.h"

Sprite2D::Sprite2D(){
    m_position=vec2(5.f);
    m_scale=vec2(5.f);
    m_rotation=0.f;
}
mat4 Sprite2D::get_transform() {
    mat4 t(1.f);
    //!!!下面三个是右乘矩阵 
    t=translate(t,vec3(m_position,0.f));
    t=rotate(t,radians(m_rotation),vec3(0.f,0.f,1.f));
    t=scale(t,vec3(m_scale,1.f));
    
    //debug("{}\n",to_string(t[3]));
    return t;
}

void Sprite2D::draw() {
    mat4 result=viewport->get_transform_mat4()*get_transform();

    drawer->draw_texture(texture_id,value_ptr(result));
}

void Sprite2D::set_texture(std::string name) {
    assert(scene);
    Render* r=scene->app->get_renderer();
    texture_id = r->get_texture(name).get_id();
}

void Sprite2D::process(float delta_time) {
    //m_position+=delta_time*1.f;
}
