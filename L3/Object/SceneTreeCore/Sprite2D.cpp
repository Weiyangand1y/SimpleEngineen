#include "Sprite2D.h"
#include "Scene.h"
#include "L1/Debug/Log.h"
#include "L1/Lib/Math/Transform2D.h"
Sprite2D::Sprite2D(){
    set_name("@Sprite2D");
    m_position=math::vec2(0.f);
    m_scale=math::vec2(0.1f);
    m_rotation=0.f;
}

void Sprite2D::draw() {
    Transform2D rect_transform;
    rect_transform.model_matrix=viewport->get_transform_mat4()*get_transform();
    Transform2D circle_transform;
    circle_transform.model_matrix=viewport->get_transform_mat4()*get_transform2();

    drawer->draw_rect(rect_transform.get_matrix_ptr());
    drawer->draw_circle(circle_transform.get_matrix_ptr(),0.9f,0.4f,0.8f,0.4f);
    drawer->draw_texture(texture_id,rect_transform.get_matrix_ptr());
}

void Sprite2D::set_texture(std::string name) {
    assert(scene);
    Render* r=scene->app->get_renderer();
    Texture& t=r->get_texture(name);
    texture_id = t.get_id();
    m_size={t.w,t.h};
    math::vec2 s2=m_scale*m_size;
    debug("sprite[{}] total size: {:.2f}, {:.2f}\n",name,s2.x,s2.y);
}

void Sprite2D::process(float delta_time) {
    
}

