#include "test08.h"
class L3App : public Application{
PhysicScene* scene;
SignalObject so;
ScriptObject script;
ImViewport iv;
AddUI add_ui;
bool running=true;

void script_binding(){
    script.script["add_tpn_node"]=[&](float x,float y){
        TexturePhysicNode* tpn=scene->create_scene_node<TexturePhysicNode>(x,y);
        scene->add_to_root_node(tpn);
    };
    script.script["rigster"]=[&](SceneNode& sn){
        scene->let_node_know_scene(&sn);
    };
    script.script["add_node"]=[&](SceneNode& sn){
        scene->add_to_root_node(&sn);
    };
    script.script["scene"]=(Scene*)scene;
    script.script.new_usertype<Sprite2D>("Sprite2D",
    sol::constructors<Sprite2D>(),
    "create_from_scene",&Sprite2D::create_from_scene,
    "set_texture",      &Sprite2D::set_texture,
    "set_position",     &Sprite2D::set_position,
    "set_scale",        static_cast<void(Sprite2D::*)(float)>(&Sprite2D::set_scale),
    sol::base_classes, sol::bases<SceneNode>()
    );
}
void script_execute(){
    script.execute(Config::getInstance().get("lua_script_file")+"test2.lua");
}
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
        script_binding();        
        //
        scene=new PhysicScene(this);
        scene->init();
        //-----------------------------
        script_execute();
        //----------------------------
        TexturePhysicNode* tpn=scene->create_scene_node<TexturePhysicNode>();
        scene->add_to_root_node(tpn);                                                                                                                                                                                                                                                                                                                                                                                                                                                      
        //----------------------------
        TexturePhysicNode* tpn2=scene->create_scene_node<TexturePhysicNode>(30.f,80.f);
        tpn2->texture_key="Claudette_Huy";
        scene->add_to_root_node(tpn2);
        //------------------------------
        so.connect_to_emit("jump",tpn2->signal,"jump");
        so.connect_to_emit("fly",tpn->signal,"fly");
        so.connect_to_emit("mb2",scene->default_viewport->signal,"click");
        //----------------------------
        RectPhysicNode* rpn=scene->create_scene_node<RectPhysicNode>();
        scene->add_to_root_node(rpn);
        //----------------------------
        FollowCamera* fc=scene->create_scene_node<FollowCamera>();
        fc->set_who_to_follow(tpn2->body);
        fc->set_camera(scene->default_viewport->get_camera());
        scene->add_to_root_node(fc);
        //----------------------------
        iv.mouse_click_callback=[&](float x,float y){
            so.emit("mb2",{x,y});
        };
        add_ui.callback=[=](float x,float y){
            TexturePhysicNode* tpn0=scene->create_scene_node<TexturePhysicNode>(x,y);
            scene->add_to_root_node(tpn0);
        };
    }
    void _run()override{
        //Sleep(5);
        if(running)
            scene->run(delta_time);
        MyImGui::static_begin();

        ImFont* imFont = MyImGui::get_imfont(0);
        ImGui::Begin("操作区域");
        ImGui::PushFont(imFont);
        
        if (RoundedButton("按下",{100,40})) {
            so.emit("jump");
        }
        if(RoundedButton("stop")){
            running=!running;
        }
        if(RoundedButton("圆")){
            Logger::log(1,"hello?");
        }
        ImGui::TextColored(ImVec4(0.5f,0.3f,0.8f,1.f),"------");
        RoundedButton("OK");
        ImGui::GetWindowDrawList()->AddCircle({50,50},100,0xff1122ff);
        ImGui::PopFont();
        ImGui::End();
        auto& io=ImGui::GetIO();
         for (int i = 0; i < io.InputQueueCharacters.Size; i++) { 
            ImWchar c = io.InputQueueCharacters[i]; 
            printf("\'%c\' (0x%04X)", (c > ' ' && c <= 255) ? (char)c : '?', c);
        }

        int id=renderer.get_framebuffer_color_texture_id("f2");
        iv.texture_id=id;
        iv.drawGui();

        add_ui.show();


        MyImGui::static_end();
    }
};

// #ifdef NO_CONSOLE
// #include <Windows.h>
// int CALLBACK WinMain(__in  HINSTANCE hInstance,__in  HINSTANCE hPrevInstance,
//    __in  LPSTR lpCmdLine, __in  int nCmdShow)
// #else
int main()
// #endif
{  
    system("chcp 65001");
    system("cls");
    std::cout<<"你好"<<std::endl;
    L3App app;
    app.init();
    app.run(); 
}