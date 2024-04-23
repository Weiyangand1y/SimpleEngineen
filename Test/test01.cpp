#include <iostream>
#include "L1/App/Application.h"
#include "L1/Lib/Math/math.h"
#include "L2/Lib/imgui/MyImGui.h"
#include "L2/Object/TaskQueue.h"
#include "L2/Lib/Net/TcpClient.h"


#include "L1/Object/ScriptObject.h"
#include "L1/Object/SignalObject.h"
#include "L1/Debug/Log.h"

#include "L4/Editor/Image/ImageLoad.h"
#include "L4/Editor/Image/ImageCut.h"
#include "L4/Editor/Image/ImageDB.h"
#include "L4/Editor/Image/ImagePlatter/ImagePlatter.h"
#include "L4/Editor/Console/ImConsole.h"

#include <thread>


class TestApplication:public Application{
    char msg[128]={0};
    char to_send[128]={0};
    MyGameClient client;
    ImgageLoad image_load;
    ImageCut image_cut;
    ImagePlatter image_platter;
    ScriptObject so;
    ImageDB image_db;
    ImConsole console;
    TimeCutQueue tq;
    static void test(Application* app){
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 100; i++)
        {
            app->get_renderer()->get_texture_db().load("bg"+std::to_string(i),"C:/Users/21wyc/Pictures/pixel/117601008_p0.png");
        }
        std::cout << "test:" << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()-start).count() << std::endl;
    }
public:
    void _init() override{
        std::thread t(test,this);
        t.detach();
        std::cout << "===============" << std::endl;
        Window* window = get_window();
        MyImGui::static_init(window->get_window());
        ImGui::GetIO().IniFilename = "test01.ini";
        renderer.get_texture_db().load(
            "bg", R"(C:\Users\21wyc\Pictures\KritaProject\bg.png)");
        image_db.set_renderer(&renderer);
        image_db.load_from_file();
        image_load.set_renderer(&renderer);
        image_load.set_db(&image_db);
        so.script.do_string("count=0");
        so.script.do_string("count=count+20");
        so.script.do_string("print(count)");
        image_cut.init(&image_db);
        image_platter.init(&image_db);
        client.read_callback=[this](const std::string& message){
            memcpy(msg,message.c_str(),message.size()+1);
        };
        client.init("127.0.0.1","8888");
        client.startAsyncRead();
    }
    void _run() override{

        client.poll();

        renderer.start_framebuffer("f1");  //--------------------
        renderer.clear_color();

        renderer.end_framebuffer();  //-------------------------

        drawer.draw_texture(renderer.get_framebuffer_color_texture_id("f1"),
                            "screen");

        MyImGui::static_begin();
        ImGui::Begin("TCP Net");
        ImGui::Text("read message:\n%s",msg);
        if(ImGui::IsWindowFocused() && ImGui::IsKeyDown(ImGuiKey_Enter)){
            ImGui::SetKeyboardFocusHere();
        }
        if(ImGui::InputText("send",to_send,128,ImGuiInputTextFlags_EnterReturnsTrue)){
            client.sendMessage(std::string(to_send));
        }
        ImGui::End();
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