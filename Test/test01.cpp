#include <iostream>
#include "L1/App/Application.h"
#include "L1/Lib/Math/math.h"
#include "L2/Lib/imgui/MyImGui.h"
#include "L2/Object/TaskQueue.h"
#include "L2/Lib/Net/TcpClient.h"
#include "L2/Lib/Net/TcpServer.h"

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
public:
    float progress_bar=0.f;
private:
    char msg[128]={0};
    char to_send[128]={0};
    char host[32]="127.0.0.1";
    char port[8]="8888";

    char server_rec_msg[128]={0};
    char server_msg[128]={0};

    MyGameClient client;
    TcpServer server;
    ImgageLoad image_load;
    ImageCut image_cut;
    ImagePlatter image_platter;
    ScriptObject so;
    ImageDB image_db;
    ImConsole console;
    TimeCutQueue tq;
    static void test(TestApplication* app){
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 100; i++)
        {
            app->get_renderer()->get_texture_db().load("bg"+std::to_string(i),"C:/Users/21wyc/Pictures/pixel/117601008_p0.png");
            app->progress_bar=(float)i/100;
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
        server.read_callback=[this](const std::string& message){
            memcpy(server_rec_msg,message.c_str(),message.size()+1);
        };
        server.init(8888);
        client.init("127.0.0.1","8888");
        client.connect_to_server();
        client.start_async_read();
    }
    void _run() override{
        server.poll();
        client.poll();

        renderer.start_framebuffer("f1");  //--------------------
        renderer.clear_color();

        renderer.end_framebuffer();  //-------------------------

        drawer.draw_texture(renderer.get_framebuffer_color_texture_id("f1"),
                            "screen");

        MyImGui::static_begin();
        ImGui::Begin("TCP Net");
        ImGui::BeginChild("Client",ImVec2{500,200},ImGuiChildFlags_Border);
        ImGui::SeparatorText("Client");
        ImGui::Text("read message:\n%s",msg);
        ImGui::InputTextWithHint("host","host",host,sizeof(host));
        ImGui::InputTextWithHint("port","port",port,sizeof(port));
        if(ImGui::Button("connect")){
            client.reconnect(host,port);
        }
        if(ImGui::IsWindowFocused() && ImGui::IsKeyDown(ImGuiKey_Enter)){
            ImGui::SetKeyboardFocusHere();
        }
        if(ImGui::InputText("send",to_send,128,ImGuiInputTextFlags_EnterReturnsTrue)){
            client.sendMessage(std::string(to_send)+"\n");
        }
        ImGui::EndChild();
        ImGui::BeginChild("Server",ImVec2{500,200},ImGuiChildFlags_Border);
        ImGui::SeparatorText("Server");
        ImGui::Text(server_rec_msg);
        ImGui::InputText("s_msg",server_msg,sizeof(server_msg));
        if(ImGui::Button("send")){
            server.sendMessage(std::string(server_msg)+"\n");
        }
        ImGui::EndChild();
        ImGui::SliderFloat("progress",&progress_bar,0,1);
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