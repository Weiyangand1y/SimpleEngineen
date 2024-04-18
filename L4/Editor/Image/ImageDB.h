#pragma once
#include "L2/Object/MyDataBase.h"
#include <sstream>
#include <fstream>
#include <iomanip>
#include "L1/Render/Renderer.h"
#include "L1/Object/SignalObject.h"
#include "L1/App/Config.h"
enum class ImageType{MainImage, SubImage};
class ImageDB{
public:
    struct MainTexture{
        std::string key;
        int texture_id;
        float aspect_ratio;
        std::string path;
    };
    struct SubTexture{
        std::string sub_key;
        std::string key;
        int texture_id;
        float left,right,top,bottom;//uv
        float aspect_ratio;
        float get_sub_aspect_ratio(){
            return ((right-left)*aspect_ratio)/(top-bottom);
        }
        float get_sub_inv_ratio(){
            return (top-bottom)/((right-left)*aspect_ratio);
        }
    };
    struct ImageScene{
        std::string key,sub_key;
        float px,py,sx,sy,r;
        int z;
    };
    MyDatabase<MainTexture> main_texture_table;
    MyDatabase<SubTexture> sub_texture_table;
    MyDatabase<ImageScene> image_scene_table;
    Render* renderer=nullptr;
    void set_renderer(Render* p_renderer){
        renderer=p_renderer;
    }
    void load_from_file(){
        ScriptObject so;
        so.execute(Config::getInstance().get("lua_script_file")+"/data/image2.lua");
        sol::table image_list=so.script["main_images"];
        TextureDB& texture_db=renderer->get_texture_db();
        for(auto& r:image_list){
            sol::table& imageTable = r.second.as<sol::table>();
            std::string name = imageTable[1];
            std::string path = imageTable[2];
            Texture* texture = texture_db.load(name,path);
            insert_main_texture(name,texture->get_id(),(float)texture->w/texture->h,path);
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
            insert_sub_texture(subkey,key,texture->get_id(),left,right,top,bottom,(float)texture->w/texture->h);
        }
    }
    void insert_main_texture(std::string key,int texture_id,float aspect_radio=1.f,std::string path=""){
        main_texture_table.insert(key,[=](MainTexture& record){
            record={key,texture_id,aspect_radio,path};
        });
    }
    void insert_sub_texture(std::string subkey,std::string key,int texture_id,
                    float left,float right,float top,float bottom,float aspect_radio=1.f){
            sub_texture_table.insert(subkey,[=](SubTexture& record){
            record={subkey,key,texture_id,left,right,top,bottom,aspect_radio};
        });
    }
    void save_to_file(){
        std::ostringstream oss;
        oss << "main_images={\n";
        main_texture_table.select_all([&](MainTexture& record){
            oss<<"\t{\n\t\t\""<<record.key<<"\",\n\t\t\""<<record.path;
            oss << "\"\n\t},\n";    
        });
        oss << "\n}";
        oss<<"\nsub_images={\n";
        sub_texture_table.select_all([&](SubTexture& record){
            oss<<"\t{\n\t\t\""<<record.sub_key<<"\",\n\t\t\""<<record.key
            <<"\",\n\t\t"<<std::fixed << std::setprecision(3)<<record.left
            <<","<<record.right<<","<<record.top<<","<<record.bottom<<"\n\t},\n";
        });
        oss << "\n}";

        std::ofstream outputFile("C:/Users/21wyc/Documents/Project/SimpleEngine/assets/Script/data/image2.lua");
        if (!outputFile.is_open()) {
            std::cerr << "Error: Unable to open the file." << std::endl;
            return; // 退出程序，表示出错
        }
        outputFile << oss.str();
        outputFile.close();
    }
};