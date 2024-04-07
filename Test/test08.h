#include "L1/Debug/Log.h"
#include "L1/App/Application.h"
#include "L1/Object/SignalObject.h"
#include "L1/Object/ScriptObject.h"
#include "L1/Lib/Math/random.hpp"

#include "L2/Lib/imgui/MyImGui.h"
#include "L2/Lib/imgui/UI/ImViewport.h"
#include "L2/Lib/imgui/UI/RoundButton.h"

#include "L3/Object/SceneTreeCore/Sprite2D.h"
#include "L3/Object/SubClass/SceneTree/PhysicScene.h"
#include "L3/Object/SubClass/SceneTree/FollowSprite2D.h"
#include "L3/Object/Mix/PhysicNode.h"
#include "L3/Object/SubClass/SceneTree/RectDraw.hpp"
#include "L3/Object/SubClass/SceneTree/FollowCamera.hpp"
#include "L3/Object/Mix/ScriptBind.h"
//#include <Windows.h>
//#include <windows.h> 

class AddUI{
public:
    float x=0.f,y=0.f;
    char textBuffer[256] = { 0 };
    std::function<void(float x,float)> callback;
    AddUI(){
        
    }
    void show(){
        ImGui::Begin("Add Node");
        ImGui::DragFloat("x",&x,5.f,-100.f,100.f);
        ImGui::DragFloat("y",&y,5.f,-100.f,100.f);
        if(ImGui::Button("Add"))callback(x,y);
        if(ImGui::InputText("##TextEdit", textBuffer, IM_ARRAYSIZE(textBuffer),
                ImGuiInputTextFlags_EnterReturnsTrue)){
                    debug("enter, text is: {}\n",textBuffer);
                };
        ImGui::SameLine();
        ImGui::SmallButton("send");
        ImGui::End();
    }
};




class TexturePhysicNode : public SceneNode{
public:
    std::string texture_key="Maki_Rollo";
    Node2D* body;
    float m_px=50.f,m_py=60.f;
    TexturePhysicNode(){
    }
    TexturePhysicNode(float px,float py){
        m_px=px;
        m_py=py;
    }
    void ready()override{
        auto* pn=create_add_child<CircleNode>();
        pn->set_transform(m_px,m_py);
        pn->set_circle_radius(9.f);
        pn->set_physic_material(1.8f,0.2f);
        //----------
        Sprite2D* s=create_add_child<Sprite2D>();
        s->set_texture(texture_key);
        s->set_who_to_follow(pn);
        body=s;
        //----------------
        // FollowSprite2D* fs=create_add_child<FollowSprite2D>();
        // body=fs;
        // fs->set_texture(texture_key);
        // fs->set_who_to_follow(pn);
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
            //fs->signal.emit("click",info);
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

        auto* gn=create_add_child<PhysicNode>(sx,sy);
        gn->set_transform(px,py,angle);
        gn->set_body_type(PhysicNode::BodyType::STATIC);

        //
        RectDraw* rd=create_add_child<RectDraw>();
        rd->set_transform(px,py,  sx,sy,  angle);
        rd->make_many();
    }
    
};
