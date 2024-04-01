#include "L1/Debug/Log.h"
#include "L1/App/Application.h"
#include "L1/Object/SignalObject.h"
#include "L1/Lib/Math/random.hpp"

#include "L2/Lib/imgui/MyImGui.h"
#include "L2/Lib/imgui/UI/ImViewport.h"

#include "L3/Object/SceneTreeCore/Sprite2D.h"
#include "L3/Object/SubClass/SceneTree/PhysicScene.h"
#include "L3/Object/SubClass/SceneTree/FollowSprite2D.h"
#include "L3/Object/Mix/PhysicNode.h"
#include "L3/Object/SubClass/SceneTree/RectDraw.hpp"
//#include <Windows.h>
//#include <windows.h> 

class TexturePhysicNode : public SceneNode{
public:
    TexturePhysicNode(){
    }
    void ready()override{
        auto* pn=new CircleNode();
        pn->set_position(50.f,60.f);
        pn->m_size={5.7f,9.f};
        scene->let_node_know_scene(pn);
        add_child(pn);
        pn->set_physic_material(1.8f,0.2f);
        //----------
        FollowSprite2D* fs=scene->create_scene_node<FollowSprite2D>();
        fs->set_texture("Maki_Rollo");
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
        float px=0.f,py=-1.f;
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

class L3App : public Application{
PhysicScene* scene;
SignalObject so;
ImViewport iv;
void init_window() {
    Window* window = get_window();
    MyImGui::static_init(window->get_window());
    window->m_key_callback = [&](int key, int scancode, int action, int mods) {
        if (key == ' ' && action == 1)so.emit("fly");
    };   
}

public:
    void _init()override{
        init_window();
        //
        scene=new PhysicScene(this);
        scene->init();
        //------------------------------
        Sprite2D* sp=scene->create_scene_node<Sprite2D>();
        sp->set_texture("Pippi_Carter");
        sp->set_position(0.f,9.f);
        scene->add_to_root_node(sp);
        //----------------------------
        TexturePhysicNode* tpn=scene->create_scene_node<TexturePhysicNode>();
        scene->add_to_root_node(tpn);
        //------------------------------
        so.connect_to_emit("jump",tpn->signal,"jump");
        so.connect_to_emit("fly",tpn->signal,"fly");
        so.connect_to_emit("mb2",scene->default_viewport->signal,"click");
        //----------------------------
        RectPhysicNode* rpn=scene->create_scene_node<RectPhysicNode>();
        scene->add_to_root_node(rpn);
        //----------------------------
        iv.mouse_click_callback=[&](float x,float y){
            so.emit("mb2",{x,y});
        };
    }
    void _run()override{
        //Sleep(5);
        scene->run(delta_time);
        MyImGui::static_begin();

        ImFont* imFont = MyImGui::get_imfont(0);
        ImGui::Begin("操作区域");
        ImGui::PushFont(imFont);
        
        if (ImGui::Button("按下",ImVec2(60,40))) {
            so.emit("jump");
        }
        ImGui::TextColored(ImVec4(0.5f,0.3f,0.8f,1.f),"------");
        ImGui::Button("OK");
        ImGui::GetWindowDrawList()->AddCircle({50,50},100,0xff1122ff);
        ImGui::PopFont();
        ImGui::End();

        int id=renderer.get_framebuffer_color_texture_id("f2");
        iv.texture_id=id;
        iv.show();

        

        MyImGui::static_end();
    }
};
int 
// CALLBACK WinMain(__in  HINSTANCE hInstance,__in  HINSTANCE hPrevInstance,
//   __in  LPSTR lpCmdLine, __in  int nCmdShow)
main()
{  
    system("chcp 65001");
    system("cls");
    std::cout<<"你好"<<std::endl;
    L3App app;
    app.init();
    app.run();
}