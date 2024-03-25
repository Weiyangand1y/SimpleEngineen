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
//#include <Windows.h>
//#include <windows.h> 
class L3App : public Application{
PhysicScene* scene;
SignalObject so;
public:
    void _init()override{
        Window* window=get_window();
        int id=so.connect("mouse_button",[](Info info){
            InfoWrapper info_wrap(info);
            int button=info_wrap.get_next_value<int>();
            int action=info_wrap.get_next_value<int>();
            int mods=info_wrap.get_next_value<int>();
            auto& io=ImGui::GetIO();
            auto pos=io.MousePos;
            // fmt::print(fg(fmt::color::aqua),"mouse button: [ {}, {} ] pos:[{}, {}]\n",
            // button?"right":"left",
            // action?"press":"release",
            // pos.x,pos.y
            // );
        });

        so.connect("mb2",[](Info info){
            InfoWrapper info_wrap(info);
            float nx=info_wrap.get_next_value<float>();
            float ny=info_wrap.get_next_value<float>();
            debug("click: {} {}\n",nx,ny);
        });

        window->m_mouse_button_callback=[&](int button, int action, int mods){
            so.emit("mouse_button",{button,action,mods});
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
            debug("angle: {:.3f}\t",angle);
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
        //Sleep(5);
        scene->run(delta_time);
        MyImGui::static_begin();

        ImFont* imFont = MyImGui::get_imfont(0);
        ImGui::Begin("操作区域");
        ImGui::PushFont(imFont);
        
        if (ImGui::Button("按下",ImVec2(60,40))) {
            so.emit("jump");
        }
        ImGui::Button("OK");
       
        ImGui::PopFont();
        ImGui::End();

        int id=renderer.get_framebuffer_color_texture_id("f2");
        ImGui::Begin("运行界面");       
        ImVec2 size = ImGui::GetWindowSize();
        ImGui::Image((void*)renderer.get_framebuffer_color_texture_id("f2"),
                         ImVec2{size.x,size.x*0.6667f}, ImVec2{0,1}, ImVec2{1,0});
        if(ImGui::IsMouseClicked(ImGuiMouseButton_Left)){
            auto p=ImGui::GetItemRectMin();
            auto q=ImGui::GetIO().MouseClickedPos[0];
            
            float delta_x=q.x-p.x;
            float delta_y=q.y-p.y;
            debug("p: {}, {}\n",delta_x,delta_y);
            so.emit("mb2",{delta_x*2/size.x-1.f,-delta_y*2/(size.x*0.6667f)+1.f});
        }
        
        ImGui::End();
        MyImGui::static_end();
    }
};
int 
// CALLBACK WinMain(__in  HINSTANCE hInstance,__in  HINSTANCE hPrevInstance,
//   __in  LPSTR lpCmdLine, __in  int nCmdShow)
main()
{  
    system("cls");
    L3App app;
    app.init();
    app.run();
}