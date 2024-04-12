#pragma once
#include "L3/Object/SceneTreeCore/DrawableNode.h"
class RectDraw : public DrawableNode{
public:
    struct Color{
        float r=0.9f,g=0.05f,b=0.1f,a=0.5f;
    };
    Color m_color;
    RectDraw(){}
    void set_transform(float px,float py,float sx=10.f,float sy=10.f,float angle=0.f){
        m_position  =   {px,py};
        m_size      =   {sx,sy};
        m_rotation  =   angle;
    }
    void draw()override{
        math::mat4 result=viewport->get_view_projection_matrix()*get_transform_matrix();
        drawer->draw_rect(value_ptr(result),m_color.r,m_color.g,m_color.b,m_color.a);
    }
    void make_many(){
        for (int i = 1; i <= 8; i++)
            make(0.2f,50.f*i);
    }
    void make(float w,float len){
        RectDraw* long_rect=scene->create_scene_node<RectDraw>();
        long_rect->m_size={w,len};
        long_rect->m_position={len,0.f};
        long_rect->m_color={0.4f,0.95f,0.95f,.4f};
        add_child(long_rect);
        RectDraw* long_rect2=scene->create_scene_node<RectDraw>();
        long_rect2->m_size={w,len};
        long_rect2->m_position={-len,0.f};
        add_child(long_rect2);
        RectDraw* long_rect3=scene->create_scene_node<RectDraw>();
        long_rect3->m_size={len,w};
        long_rect3->m_position={0.f,len};
        add_child(long_rect3);
        RectDraw* long_rect4=scene->create_scene_node<RectDraw>();
        long_rect4->m_size={len,w};
        long_rect4->m_position={0.f,-len};
        add_child(long_rect4);
    }
};