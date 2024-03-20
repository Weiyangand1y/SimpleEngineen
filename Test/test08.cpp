#include "L1/Debug/Log.h"
#include "L1/App/Application.h"
#include "L1/Object/SignalObject.h"
#include "L1/Lib/Math/random.hpp"

#include "L2/Lib/imgui/MyImGui.h"

#include "L3/Object/SceneTreeCore/Sprite2D.h"
#include "L3/Object/SubClass/SceneTree/PhysicScene.h"
#include "L3/Object/SubClass/SceneTree/FollowSprite2D.h"
#include "L3/Object/Mix/PhysicNode.h"
#include "L3/Object/SubClass/SceneTree/RectDraw.hpp"
#include <Windows.h>
class L3App : public Application{
PhysicScene* scene;
SignalObject so;
public:
    void _init()override{
        Window* window=get_window();
        int id=so.connect("mouse_move",[](Info info){
            InfoWrapper info_wrap(info);
                double x=std::any_cast<double>(info[0]);
                double y=std::any_cast<double>(info[1]);
                //fmt::print(fg(fmt::color::aqua),"cursor pos: [ {}, {} ]\n",x,y);
        });

        window->m_cursor_pos_callback=[&](double xpos,double ypos){
            so.emit("mouse_move",{xpos,ypos});
        };
        window->m_key_callback=[&](int key, int scancode, int action, int mods){
            if(key==' ' && action==1)so.emit("fly");
        };

        MyImGui::static_init(window->get_window());
        //------------------------------
        scene=new PhysicScene(this);
        scene->init();
        //
        Sprite2D* sp=scene->create_scene_node<Sprite2D>();
        sp->set_texture("Pippi_Carter");
        sp->set_position(0.f,9.f);
        scene->root_node->add_child(sp);
        //-----------------------------
        auto* pn=new CircleNode();
        pn->set_position(50.f,60.f);
        pn->m_size={5.7f,9.f};
        scene->let_node_know_scene(pn);
        scene->root_node->add_child(pn);
        pn->set_physic_material(1.8f,0.2f);
        //----------------------------
        so.connect("jump",[=](Info info){
            pn->set_init_speed(30.f,10.f);
        });
        so.connect("fly",[=](Info info){
            RandomGenerator rgt;
            float angle=rgt.getRandomFloat(1.4f,1.8f);
            debug("angle: {}",angle);
            pn->set_init_speed(cosf(angle)*20.f,sinf(angle)*20.f);
        });
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
        rd->m_size={100.f,0.2f};
        rd->m_position={0.f,-0.2f};
        rd->m_rotation=0.2f;
        scene->root_node->add_child(rd);
        rd->make_many();
    }
    void _run()override{
        scene->run(delta_time);
        MyImGui::static_begin();

        ImFont* imFont = MyImGui::get_imfont(1);
        ImGui::Begin("---------------",nullptr,ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground);
        ImGui::PushFont(imFont);
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.9f, 0.4f, 0.4f, 1.f)); 
        if (ImGui::Button("按下",ImVec2(100,50))) {
            so.emit("jump");
        }
        ImGui::PopStyleColor();
        ImGui::PopFont();
        ImGui::End();


        ImVec2 text_pos=ImGui::GetWindowPos()+ImVec2{100,100};
        ImGui::GetForegroundDrawList()
                        ->AddText(imFont,48.0f,text_pos,0xffffffff,
                        "将所绘制的文字都\n放到一个较大的纹理上去");
        ImGui::GetForegroundDrawList()->AddCircle(text_pos,10,0xff1166ff);

        MyImGui::static_end();
    }
};
int CALLBACK WinMain(__in  HINSTANCE hInstance,__in  HINSTANCE hPrevInstance,
  __in  LPSTR lpCmdLine, __in  int nCmdShow){
    
    system("cls");
    L3App app;
    app.init();
    app.run();
}