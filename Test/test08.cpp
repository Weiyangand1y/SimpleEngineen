#include "test08.h"
#include <chrono>
#include "L1/Render/extension/ShaderDrawer.h"
#include "L1/Debug/TimeMeasure.h"

std::string UnicodeToUTF8(unsigned int codepoint) {
    std::string out;

    if (codepoint <= 0x7f) {
        out.append(1, static_cast<char>(codepoint));
    } else if (codepoint <= 0x7ff) {
        out.append(1, static_cast<char>(0xc0 | ((codepoint >> 6) & 0x1f)));
        out.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
    } else if (codepoint <= 0xffff) {
        out.append(1, static_cast<char>(0xe0 | ((codepoint >> 12) & 0x0f)));
        out.append(1, static_cast<char>(0x80 | ((codepoint >> 6) & 0x3f)));
        out.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
    } else {
        out.append(1, static_cast<char>(0xf0 | ((codepoint >> 18) & 0x07)));
        out.append(1, static_cast<char>(0x80 | ((codepoint >> 12) & 0x3f)));
        out.append(1, static_cast<char>(0x80 | ((codepoint >> 6) & 0x3f)));
        out.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
    }
    return out;
}

std::string UnicodeSeqToUTF8(const std::vector<unsigned int>& unicodeSeq) {
    std::string utf8Str;
    for (auto codepoint : unicodeSeq) {
        utf8Str += UnicodeToUTF8(codepoint);
    }
    return utf8Str;
}


class L3App : public Application{
PhysicScene* scene;
SignalObject so;
ScriptObject script;
ImViewport iv;
AddUI add_ui;
bool running=true;
ShaderDrawer sd;

void script_binding(){
    script.script["add_tpn_node"]=[&](float x,float y){
        TexturePhysicNode* tpn=scene->create_scene_node<TexturePhysicNode>(x,y);
        scene->add_to_root_node(tpn);
    };
    script.script["rigster"]=[&](SceneNode& sn){
        scene->make_enter_scene(&sn);
    };
    script.script["add_node"]=[&](SceneNode& sn){
        scene->add_to_root_node(&sn);
    };
    script.script["scene"]=(Scene*)scene;

    script_bind_class(script.script);
}
void script_execute(){
    script.script.require_file("test",Config::getInstance().get("lua_script_file")+"make_simple.lua");
    script.execute(Config::getInstance().get("lua_script_file")+"test2.lua");
}
void init_window() {
    sd.set_render(renderer);
    Window* window = get_window();
    MyImGui::static_init(window->get_window());
    window->m_key_callback = [&](int key, int scancode, int action, int mods) {
        if(action==1){
            if(key==' ')so.emit("fly");
            else if(key=='A')so.emit("left");
            else if(key=='D')so.emit("right");
            else if(key=='W')so.emit("up");
            else if(key=='S')so.emit("down");
        }
    };   
}

public:
    void _init()override{

    MEASURE_TIME(
        init_window();
        script_binding();        
        //
        scene=new PhysicScene(this);
        scene->init();
        //-----------------------------
        script_execute();
        );
        //----------------------------
        auto n1=scene->root_node->create_add_child<SceneNode>();
        n1->connect_signal(so,"hello",[](const Info&){debug("***n1\n")});
        auto n2=scene->root_node->create_add_child<SceneNode>();
        n2->connect_signal(so,"hello",[](const Info&){debug("***n2\n")});
        auto n3=scene->root_node->create_add_child<SceneNode>();
        n3->connect_signal(so,"hello",[](const Info&){debug("***n3\n")});
        auto n4=n1->create_add_child<SceneNode>();
        n4->connect_signal(so,"hello",[](const Info&){debug("***n4\n")});
        so.emit("hello");
        n1->queue_free();
        scene->do_queue_free();
        debug("---after free\n");
        so.emit("hello");

        //----------------------------
        TexturePhysicNode* tpn=scene->create_scene_node<TexturePhysicNode>();
        scene->add_to_root_node(tpn); 
        PhysicNodeController* pnc=new PhysicNodeController(tpn->mpn);
        pnc->connect_signal(so); 

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
        fc->set_who_to_follow(tpn->body);
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
        ImGuiIO& io = ImGui::GetIO();               
        if(io.InputQueueCharacters.Size>0){
            char buf[64]={0};
            ImGui::ImTextStrToUtf8(buf,64,io.InputQueueCharacters.begin(),io.InputQueueCharacters.end());
            printf("pinyin: %s\n",buf);
        }
            
        int id=renderer.get_framebuffer_color_texture_id("f2");
        iv.texture_id=id;
        iv.drawGui();

        add_ui.show();

        
        MyImGui::static_end();
        mat4 m=mat4(1.f);
        sd.draw(value_ptr(m),time);
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