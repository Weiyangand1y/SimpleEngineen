#pragma once
#include "L2/Lib/imgui/MyImGui.h"
#include "L1/Render/Renderer.h"
#include "ImageDB.h"
#include "L1/Object/SignalObject.h"
#include "L1/App/Config.h"
class ImgageLoad{
    struct ImageLoadData{
        char path_text[128]={0};
        char key_text[64]={0};
        int texture_id=-1;
        float texture_aspect_radio=-1.f;
    };
    ImageLoadData data;
    Render* renderer=nullptr;
    ImageDB* image_db=nullptr;
public:
    ImgageLoad(){}
    void set_renderer(Render* p_renderer){renderer=p_renderer;}
    void set_db(ImageDB* p_image_db){
        image_db=p_image_db;
        ScriptObject so;
        so.execute(Config::getInstance().get("lua_script_file")+"/data/image2.lua");
        sol::table image_list=so.script["main_images"];
        TextureDB& texture_db=renderer->get_texture_db();
        for(auto& r:image_list){
            sol::table& imageTable = r.second.as<sol::table>();
            std::string name = imageTable[1];
            std::string path = imageTable[2];
            Texture* texture = texture_db.load(name,path);
            image_db->insert_main_texture(name,texture->get_id(),(float)texture->w/texture->h,path);
        }
        sol::table sub_image_list=so.script["sub_images"];
            for(auto& r:sub_image_list){
            sol::table& imageTable = r.second.as<sol::table>();
            std::string subkey = imageTable[1];
            std::string key = imageTable[2];
            Texture* texture = &texture_db.get_texture(key);
            float left=imageTable[3];
            float right=imageTable[4];
            float top=imageTable[5];
            float bottom=imageTable[6];
            image_db->insert_sub_texture(subkey,key,texture->get_id(),left,right,top,bottom);
        }
        }
    void save_and_flush(){
        renderer->get_texture_db().load(std::string(data.key_text),std::string(data.path_text));
        Texture& texture=renderer->get_texture(std::string(data.key_text));
        data.texture_id=texture.get_id();
        data.texture_aspect_radio=(float)texture.w/texture.h;
        image_db->insert_main_texture(
            std::string(data.key_text),texture.get_id(),
            data.texture_aspect_radio,std::string(data.path_text)
            );
        image_db->save_to_file();
    }
    void update_key_from_path(){
        std::string path=std::string(data.path_text);
        size_t from=path.find_last_of('/');
        size_t to=path.find_last_of('.');
        std::string filename = path.substr(from+1,to-from-1);
        std::strncpy(data.key_text,filename.c_str(),63);
    }
    void render(){       
    ImGui::Begin("Image Load");
        float window_width=ImGui::GetWindowWidth();
        auto& io=ImGui::GetIO();
        ImGui::Text("path:(key enter to let filename to be the key)");
        ImGui::SetNextItemWidth(window_width-20);
        if(ImGui::InputText("##path",data.path_text,sizeof(data.path_text),ImGuiInputTextFlags_EnterReturnsTrue)){
            update_key_from_path();
        }
        ImGui::Text("key:");
        ImGui::InputText("##key",data.key_text,sizeof(data.key_text));
        if(ImGui::Button("Load Image(Ctrl+S)")){
            save_and_flush();
        }
        if(data.texture_id!=-1){
            ImGui::SeparatorText("Image");            
            ImGui::Image(
                (void*)(intptr_t)data.texture_id,
                {window_width-20,window_width/data.texture_aspect_radio},
                {0,1},{1,0}
            );
        }
        if(ImGui::IsWindowFocused()&&io.KeyCtrl&&ImGui::IsKeyPressed(ImGuiKey_S)){
            save_and_flush();
        }
    ImGui::End();
    }
};