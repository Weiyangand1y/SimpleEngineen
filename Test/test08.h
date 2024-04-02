#include "L1/Debug/Log.h"
#include "L1/App/Application.h"
#include "L1/Object/SignalObject.h"
#include "L1/Object/ScriptObject.h"
#include "L1/Lib/Math/random.hpp"

#include "L2/Lib/imgui/MyImGui.h"
#include "L2/Lib/imgui/UI/ImViewport.h"

#include "L3/Object/SceneTreeCore/Sprite2D.h"
#include "L3/Object/SubClass/SceneTree/PhysicScene.h"
#include "L3/Object/SubClass/SceneTree/FollowSprite2D.h"
#include "L3/Object/Mix/PhysicNode.h"
#include "L3/Object/SubClass/SceneTree/RectDraw.hpp"
#include "L3/Object/SubClass/SceneTree/FollowCamera.hpp"

//#include <Windows.h>
//#include <windows.h> 

class AddUI{
public:
    float x=0.f,y=0.f;
    std::function<void(float x,float)> callback;
    void show(){
        ImGui::Begin("Add Node");
        ImGui::DragFloat("x",&x,5.f,-100.f,100.f);
        ImGui::DragFloat("y",&y,5.f,-100.f,100.f);
        if(ImGui::Button("Add"))callback(x,y);
        ImGui::End();
    }
};


class TexturePhysicNode : public SceneNode{
public:
    std::string texture_key="Maki_Rollo";
    Node2D* body=nullptr;
    float m_px=50.f,m_py=60.f;
    TexturePhysicNode(){
    }
    TexturePhysicNode(float px,float py){
        m_px=px;
        m_py=py;
    }
    void ready()override{
        auto* pn=new CircleNode();
        pn->set_position(m_px,m_py);
        pn->m_size={5.7f,9.f};
        scene->let_node_know_scene(pn);
        add_child(pn);
        pn->set_physic_material(1.8f,0.2f);
        //----------
        FollowSprite2D* fs=scene->create_scene_node<FollowSprite2D>();
        body=fs;
        fs->set_texture(texture_key);
        fs->set_who_to_follow(pn);
        add_child(fs);
        //----------------
        signal.connect("jump",[=](const Info& info){
            pn->set_init_speed(30.f,10.f);
        });
        signal.connect("fly",[=](const Info& info){
            RandomGenerator rgt;
            float angle=rgt.getRandomFloat(1.4f,1.8f);
            debug("angle: {:.3f}\t",angle);
            pn->set_init_speed(cosf(angle)*20.f,sinf(angle)*20.f);
        });
               
        viewport->signal.connect("click",[=](const Info& info){
            fs->signal.emit("click",info);
        });
        
        
    }

};

class RectPhysicNode : public SceneNode{
public:
    RectPhysicNode(){}
    void ready()override{
        float px=0.f,py=-10.f;
        float sx=100.f,sy=10.f;
        float angle=0.2f;

        PhysicNode* gn=new PhysicNode();
        gn->set_position(px,py);
        gn->m_size  =   {sx,sy};
        gn->m_rotation=angle;
        gn->body_type=PhysicNode::BodyType::STATIC;
        scene->let_node_know_scene(gn);
        add_child(gn);
        //
        RectDraw* rd=scene->create_scene_node<RectDraw>();
        rd->set_transform(px,py,  sx,sy,  angle);
        add_child(rd);
        rd->make_many();
    }
    
};
