#include <iostream>
#include "L1/App/Application.h"
#include "L1/Lib/Math/math.h"
#include "L2/Lib/imgui/MyImGui.h"
#include "L1/Object/ScriptObject.h"
#include "L1/Object/SignalObject.h"
#define FMT_HEADER_ONLY 
#include "fmt/core.h"
#include "fmt/color.h"
#include "L2/Object/FunObject/Sprite2D.h"

class TestApplication:public Application{
public:
    SignalObject so;
    std::vector<Sprite2D> sprite2d_list;
    void _init() override{
        std::cout<<"==============="<<std::endl;

        Window* window=get_window();
        so.connect("mouse_move",[](Info info){
            InfoWrapper info_wrap(info);
                double x=std::any_cast<double>(info[0]);
                double y=std::any_cast<double>(info[1]);
                //fmt::print(fg(fmt::color::aqua),"cursor pos: [ {}, {} ]\n",x,y);
        });
        sprite2d_list.resize(10);
        
        window->m_cursor_pos_callback=[&](double xpos,double ypos){
            so.emit("mouse_move",{xpos,ypos});
        };
        MyImGui::static_init(window->get_window());
        ScriptObject so;              
    }
    void _run() override{
        renderer.start_framebuffer("f1");  //--------------------
        renderer.clear_color();
        
        for(auto& s:sprite2d_list){
            s._move(sin(time)*0.01f,cos(time)*0.01f);
            s._rotate(tanh(time)*0.01f);
            drawer.draw_texture(std::string("Claudette_Huy"),value_ptr(s.get_transform_mat4()) );
        }

        renderer.end_framebuffer();  //-------------------------

        drawer.draw_texture(renderer.get_framebuffer_color_texture_id("f1"),
                            "screen");

        MyImGui::static_begin();
        ImGui::Begin("Image");
        ImGui::Image((ImTextureID)renderer.get_framebuffer_color_texture_id("f1"),
                         ImVec2{300.f,300.f}, ImVec2{0,1}, ImVec2{1,0});
        ImGui::End();
        MyImGui::static_end();
    }
};

int main(){
    system("cls");
    TestApplication app;
    app.init();
    app.run();
}