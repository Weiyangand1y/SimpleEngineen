#include <iostream>
#include "L1/App/Application.h"
#include "L1/Lib/Math/math.h"
#include "L2/Lib/imgui/MyImGui.h"
#include "L1/Object/ScriptObject.h"
#include "L1/Object/SignalObject.h"
#include "L1/Debug/Log.h"


class TestApplication:public Application{
public:
    SignalObject so;
    void _init() override{
        std::cout<<"==============="<<std::endl;

        Window* window=get_window();
        int id=so.connect("mouse_move",[](Info info){
            InfoWrapper info_wrap(info);
                double x=std::any_cast<double>(info[0]);
                double y=std::any_cast<double>(info[1]);
                //fmt::print(fg(fmt::color::aqua),"cursor pos: [ {}, {} ]\n",x,y);
        });
        debug("signal object's id: {}\n",id);

        window->m_cursor_pos_callback=[&](double xpos,double ypos){
            so.emit("mouse_move",{xpos,ypos});
        };
        MyImGui::static_init(window->get_window());
        ScriptObject so;
        renderer.get_texture_db().load("kairo",R"(C:\Users\21wyc\Pictures\Sugar_Kairo.png)");          
    }
    void _run() override{
        //debug("{}\n",1/delta_time);
        renderer.start_framebuffer("f1");  //--------------------
        renderer.clear_color();
        

        drawer.draw_texture("kairo");

        renderer.end_framebuffer();  //-------------------------

        drawer.draw_texture(renderer.get_framebuffer_color_texture_id("f1"),
                            "screen");

        MyImGui::static_begin();

        ImGui::Begin("Image");

        ImGui::Image((ImTextureID)renderer.get_framebuffer_color_texture_id("f1"),
                         ImVec2{300.f,300.f}, ImVec2{0,1}, ImVec2{1,0});
        ImGui::End();
        ImFont* imFont = MyImGui::get_imfont(1);
        ImVec2 text_pos=ImGui::GetWindowPos()+ImVec2{100,100};
        ImGui::GetForegroundDrawList()
                        ->AddText(imFont,48.0f,text_pos,0xffffffff,
                        "将所绘制的文字都\n放到一个较大的纹理上去");
        ImGui::GetForegroundDrawList()->AddCircle(text_pos,10,0xff1166ff);
        MyImGui::static_end();
    }
};

int main(){
    system("cls");
    TestApplication app;
    app.init();
    app.run();
}