#include <iostream>
#include "L1/App/Application.h"
#include "L1/Lib/Math/math.h"
#include "L2/Lib/imgui/MyImGui.h"

#include "L1/Object/ScriptObject.h"
#include "L1/Object/SignalObject.h"
#include "L1/Debug/Log.h"

#include "L4/Editor/Image/ImageLoad.h"
#include "L4/Editor/Image/ImageCut.h"
#include "L4/Editor/Image/ImageDB.h"
#include "L4/Editor/Image/ImagePlatter.h"
#include "L4/Editor/Console/ImConsole.h"

class TestApplication:public Application{
    struct Context{
        char image_key[64]={0};
        char text[64]={0};
        char input_image_key[64]={0};
        int texture_id=-1;
        char t3[128]={0};
    };
    Context context;
    ImgageLoad image_load;
    ImageCut image_cut;
    ImagePlatter image_platter;
    ScriptObject so;
    ImageDB image_db;
    ImConsole console;
public:
    void _init() override{
        std::cout << "===============" << std::endl;
        Window* window = get_window();
        MyImGui::static_init(window->get_window());
        ImGui::GetIO().IniFilename = "test01.ini";
        renderer.get_texture_db().load(
            "bg", R"(C:\Users\21wyc\Pictures\KritaProject\bg.png)");

        image_load.set_renderer(&renderer);
        image_load.set_db(&image_db);
        so.script.do_string("count=0");
        so.script.do_string("count=count+20");
        so.script.do_string("print(count)");
        image_cut.init(&image_db);
        image_platter.init(&image_db);
    
    }
    void _run() override{
        //debug("{}\n",1/delta_time);
        renderer.start_framebuffer("f1");  //--------------------
        renderer.clear_color();

        renderer.end_framebuffer();  //-------------------------

        drawer.draw_texture(renderer.get_framebuffer_color_texture_id("f1"),
                            "screen");

        MyImGui::static_begin();
        auto& io=ImGui::GetIO();
    {   
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding,{0,0});
        ImGui::Begin("Image",nullptr,ImGuiWindowFlags_NoTitleBar);
        ImVec2 windowPos = ImGui::GetWindowPos();
        ImVec2 windowSize = ImGui::GetWindowSize();
        auto* wdl=ImGui::GetWindowDrawList();
        wdl->AddImage((void*)(intptr_t)renderer.get_texture("bg").get_id(),
        windowPos, ImVec2(windowPos.x + windowSize.x, windowPos.y + windowSize.y),
        {0,1},{1,0}
        );
        float offset_y=16,height=80;
        wdl->AddRectFilled({windowPos.x+20,windowPos.y+offset_y},ImVec2(windowPos.x + windowSize.x/3, windowPos.y + height),ImColor(203,207,86));
        wdl->AddRectFilled(ImVec2(windowPos.x + windowSize.x/3, windowPos.y+offset_y),ImVec2(windowPos.x + windowSize.x*2/3, windowPos.y + height),IM_COL32(150,176,139,255));
        wdl->AddRectFilled(ImVec2(windowPos.x + windowSize.x*2/3, windowPos.y+offset_y),ImVec2(windowPos.x + windowSize.x-18, windowPos.y + height),IM_COL32(206,126,111,255));
        
        ImGui::SetCursorPos({50,100});
        ImGui::SetNextItemWidth(160);
        if(ImGui::InputText("image_key",context.image_key,64,ImGuiInputTextFlags_EnterReturnsTrue)){
            renderer.get_texture_db().load(std::string(context.image_key),std::string(context.text));
        }
        ImGui::SetCursorPosX(50);
        ImGui::SetNextItemWidth(260);
        if(ImGui::InputText("text",context.text,64,ImGuiInputTextFlags_EnterReturnsTrue)){
            
        }
        ImGui::SetCursorPosX(50);
        ImGui::SetNextItemWidth(160);
        if(ImGui::InputText("in_image_key",context.input_image_key,64,ImGuiInputTextFlags_EnterReturnsTrue)){
            context.texture_id=renderer.get_texture(std::string(context.input_image_key)).get_id();
        }
        ImGui::SetCursorPosX(50);
        if(context.texture_id!=-1){
            ImGui::Image((void*)(intptr_t)context.texture_id,{200,200},{0,1},{1,0});
        }
        ImGui::PopStyleVar();

        ImGui::End();}
        
        image_load.render();
        image_cut.render();
        image_platter.render();
        console.render();
        MyImGui::static_end();
    }
};

int main(){
    system("cls");
    TestApplication app;
    app.init();
    app.run();
}