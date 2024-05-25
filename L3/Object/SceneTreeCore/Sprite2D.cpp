#include "Sprite2D.h"
#include "Scene.h"
#include "L1/Debug/Log.h"
#include "L1/Lib/Math/Transform2D.h"
Sprite2D::Sprite2D(){
    set_name("@Sprite2D");
    class_name="Sprite2D";
    m_position  =   math::vec2(0.0f);
    m_scale     =   math::vec2(0.1f);
    m_rotation  =   0.f;
}

void Sprite2D::draw() {
    Transform2D rect_transform;
    rect_transform.model_matrix=viewport->get_view_projection_matrix()*get_transform_matrix();
    //>>debug draw
    Transform2D circle_transform;
    circle_transform.model_matrix=viewport->get_view_projection_matrix()*get_transform_square_matrix();

    drawer->draw_rect(rect_transform.get_matrix_ptr());
    drawer->draw_circle(circle_transform.get_matrix_ptr(),0.9f,0.4f,0.8f,0.4f);
    //<<debug draw
    drawer->draw_texture(texture_id,rect_transform.get_matrix_ptr());
}

void Sprite2D::set_texture(const std::string& name) {
    assert(scene);
    Render* renderer=scene->app->get_renderer();
    Texture& texture=renderer->get_texture(name);
    texture_id = texture.get_id();
    //
    m_size={texture.w,texture.h};
    math::vec2 s2=m_scale*m_size;
    debug("sprite[{}] total size: {:.2f}, {:.2f}\n",name,s2.x,s2.y);
    texture_key=name.c_str();
    //
}



