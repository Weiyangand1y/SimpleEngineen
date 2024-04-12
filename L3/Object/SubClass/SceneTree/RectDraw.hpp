#pragma once
#include "L3/Object/SceneTreeCore/DrawableNode.h"
class RectDraw : public DrawableNode{
public:
    struct Color{
        //float r=0.1f,g=0.9f,b=0.12f,a=0.5f;
        float r=0.9f,g=0.05f,b=0.1f,a=0.5f;
    };
    Color m_color;
    RectDraw(){}
    void set_transform(float px,float py,float sx=10.f,float sy=10.f,float angle=0.f){
        m_position={px,py};
        m_size={sx,sy};
        m_rotation=angle;
    }
    void draw()override{
        math::mat4 result=viewport->get_transform_mat4()*get_transform();
        drawer->draw_rect(value_ptr(result),m_color.r,m_color.g,m_color.b,m_color.a);
    }
    void make_many(){
        make(0.2f,50.f);
        make(0.2f,100.f);
        make(0.2f,150.f);
    }
    void make(float w,float len){
        RectDraw* rd=scene->create_scene_node<RectDraw>();
        rd->m_size={w,len};
        rd->m_position={len,0.f};
        rd->m_color={0.4f,0.95f,0.95f,.4f};
        add_child(rd);
        RectDraw* rd2=scene->create_scene_node<RectDraw>();
        rd2->m_size={w,len};
        rd2->m_position={-len,0.f};
        add_child(rd2);
        RectDraw* rd3=scene->create_scene_node<RectDraw>();
        rd3->m_size={len,w};
        rd3->m_position={0.f,len};
        add_child(rd3);
        RectDraw* rd4=scene->create_scene_node<RectDraw>();
        rd4->m_size={len,w};
        rd4->m_position={0.f,-len};
        add_child(rd4);
    }
};