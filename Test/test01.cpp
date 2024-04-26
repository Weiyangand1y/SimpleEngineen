#include <iostream>
#include "L1/App/Application.h"
#include "L1/Lib/Math/math.h"
#include "L2/Lib/imgui/MyImGui.h"
#include "L2/Lib/imgui/UI/RoundButton.h"

#include "L2/Object/TaskQueue.h"
#include "L2/Lib/Net/TcpClient.h"
#include "L2/Lib/Net/TcpServer.h"

#include "L1/Object/ScriptObject.h"
#include "L1/Object/SignalObject.h"
#include "L1/Debug/Log.h"
#include "L1/ResourceManger/TextureAsyncLoader.h"

#include "L4/Editor/Image/ImageLoad.h"
#include "L4/Editor/Image/ImageCut.h"
#include "L4/Editor/Image/ImageDB.h"
#include "L4/Editor/Image/ImagePlatter/ImagePlatter.h"
#include "L4/Editor/Console/ImConsole.h"

#include "L2/Lib/imgui/UI/AButton.h"
#include "L2/Lib/imgui/Description/FlatDescription.h"
#include "L2/Lib/Audio/AudioPlayer.h"


class TestApplication:public Application{
public:
    float progress_bar=0.f;
private:
    char msg[128]={0};
    char to_send[128]="Hello from client";
    char host[32]="127.0.0.1";
    char port[8]="8888";

    char server_rec_msg[128]={0};
    char server_msg[128]="Hello from server";
    int server_port=8888;

    MyGameClient client;
    TcpServer server;
    ImgageLoad image_load;
    ImageCut image_cut;
    ImagePlatter image_platter;
    ScriptObject so;
    ImageDB image_db;
    ImConsole console;
    AudioPlayer audio_player;
public:
    void _init() override{
        std::cout << "===============" << std::endl;
        Window* window = get_window();
        MyImGui::static_init(window->get_window());
        ImGui::GetIO().IniFilename = "test01.ini";

        image_db.set_renderer(&renderer);
        

        image_load.set_renderer(&renderer);
        image_load.set_db(&image_db);
        so.script.do_string("count=0");
        so.script.do_string("count=count+20");
        so.script.do_string("print(count)");

        image_cut.init(&image_db);
        image_platter.init(&image_db);
        image_db.async_load_image();
        
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
        image_db.update();
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
        ImGui::Text("Client recieve message:\n%s",msg);
        ImGui::Text("Host=>");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(250);
        ImGui::InputTextWithHint("##host","host",host,sizeof(host));
        ImGui::SameLine();
        ImGui::Text("Port=>");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(100);
        ImGui::InputTextWithHint("##port","port",port,sizeof(port));
        if(ImGui::Button("connect")){
            client.reconnect(host,port);
        }
        if(ImGui::IsWindowFocused() && ImGui::IsKeyDown(ImGuiKey_Enter)){
            ImGui::SetKeyboardFocusHere();
        }
        if(ImGui::InputText("##send",to_send,128,ImGuiInputTextFlags_EnterReturnsTrue)){
            client.sendMessage(std::string(to_send)+"\n");
        }
        ImGui::SameLine();
        if(AButton("Send",renderer.get_texture("cake").get_id())){
            client.sendMessage(std::string(to_send)+"\n");
        }
        ImGui::EndChild();
        if(ImGui::GetContentRegionAvail().x>800)
            ImGui::SameLine();
        ImGui::BeginChild("Server",ImVec2{500,200},ImGuiChildFlags_Border);
        ImGui::SeparatorText("Server");
        ImGui::Text("Server recieve: \n%s",server_rec_msg);
        ImGui::InputText("##s_msg",server_msg,sizeof(server_msg));
        ImGui::SameLine();
        if(RoundedButton("Send")){
            server.sendMessage(std::string(server_msg)+"\n");
        }
        if(ImGui::Button("stop")){
            server.stopListening();
        }
        ImGui::InputInt("port",&server_port);
        if(ImGui::Button("start")){
            server.startListening(server_port);
        }
        ImGui::EndChild();
        if(progress_bar<0.985f){
            ImGui::Text("Loading Images...");
            ImGui::SliderFloat("progress",&progress_bar,0,1);
        }else{
            ImGui::Text("Load Finish");
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