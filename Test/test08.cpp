#include "L1/Debug/Log.h"
#include "L1/App/Application.h"

#include "L3/Object/SceneTreeCore/Sprite2D.h"
#include "L3/Object/SubClass/SceneTree/PhysicScene.h"
#include "L3/Object/SubClass/SceneTree/FollowSprite2D.h"
#include "L3/Object/Mix/PhysicNode.h"
#include "L3/Object/SubClass/SceneTree/RectDraw.hpp"
class L3App : public Application{
PhysicScene* scene;
void draw_line(){
    RectDraw* rd=scene->create_scene_node<RectDraw>();
        rd->m_size={0.5f,100.f};
        rd->m_position={100.f,0.f};
        scene->root_node->add_child(rd);
    RectDraw* rd2=scene->create_scene_node<RectDraw>();
        rd2->m_size={0.5f,100.f};
        rd2->m_position={-100.f,0.f};
        scene->root_node->add_child(rd2);
    RectDraw* rd3=scene->create_scene_node<RectDraw>();
        rd3->m_size={100.f,0.5f};
        rd3->m_position={0.f,50.f};
        scene->root_node->add_child(rd3);
    RectDraw* rd4=scene->create_scene_node<RectDraw>();
        rd4->m_size={100.f,0.5f};
        rd4->m_position={0.f,-50.f};
        scene->root_node->add_child(rd4);
}
public:
    void _init()override{
        scene=new PhysicScene(this);
        scene->init();
        //
        Sprite2D* sp=scene->create_scene_node<Sprite2D>();
        sp->set_texture("Pippi_Carter");
        sp->set_position(0.f,9.f);
        scene->root_node->add_child(sp);
        //-----------------------------
        PhysicNode* pn=new PhysicNode();
        pn->set_position(50.f,60.f);
        pn->m_size={5.7f,9.f};
        scene->let_node_know_scene(pn);
        scene->root_node->add_child(pn);
        pn->set_physic_material(.2f,1.2f);
        //----------------------------
        FollowSprite2D* fs=scene->create_scene_node<FollowSprite2D>();
        fs->set_texture("Maki_Rollo");
        fs->set_who_to_follow(pn);
        scene->root_node->add_child(fs);
        //----------------------------
        PhysicNode* gn=new PhysicNode();
        gn->set_position(0.f   , -1.f  );
        gn->m_size  =   {100.f , 1.f  };
        gn->m_rotation=0.2f;
        gn->body_type=PhysicNode::BodyType::STATIC;
        scene->let_node_know_scene(gn);
        scene->root_node->add_child(gn);
        //
        RectDraw* rd=scene->create_scene_node<RectDraw>();
        rd->m_size={100.f,1.f};
        rd->m_position={0.f,-1.f};
        rd->m_rotation=0.2f;
        scene->root_node->add_child(rd);
        draw_line();
    }
    void _run()override{
        scene->run(delta_time);
    }
};
int main(){
    system("cls");
    L3App app;
    app.init();
    app.run();
}