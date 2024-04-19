#pragma once
#include "L2/Object/MyDataBase.h"
#include <sstream>
#include <fstream>
#include <iomanip>
#include "L1/Render/Renderer.h"
#include "L1/Object/SignalObject.h"
#include "L1/App/Config.h"
#include "L1/Debug/TimeMeasure.h"

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
    // std::unordered_map<std::string,std::vector<std::string>> image_tasks;
    // void async_load_image(){
    //     ScriptObject so;
    //     so.execute(Config::getInstance().get("lua_script_file")+"/data/image2.lua");
    //     sol::table image_list=so.script["main_images"];
    //     int n=5;
    //     for(int i=0;i<n;i++){
    //         sol::table& imageTable = image_list[i]second.as<sol::table>();
    //         std::string name = imageTable[1];
    //         image_tasks[name].push_back()
    //     }
    // }
    void load_from_file(){
        //异步图像加载功能
        MEASURE_TIME(
        ScriptObject so;
        so.execute(Config::getInstance().get("lua_script_file")+"/data/image2.lua");
        sol::table image_list=so.script["main_images"];

        TextureDB& texture_db=renderer->get_texture_db();
        ) 
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
    void load_scene_from_file(){
        ScriptObject so;
        so.execute(Config::getInstance().get("lua_script_file")+"/data/image_scene.lua");
        sol::table image_list=so.script["image_scene"];
        for(auto& r:image_list){
            sol::table& imageTable = r.second.as<sol::table>();
            std::string key = imageTable[1];
            std::string sub_key = imageTable[2];
            float px = imageTable[3];
            float py = imageTable[4];
            float sx = imageTable[5];
            float sy = imageTable[6];
            float r = imageTable[7];
            int z = imageTable[8];
            image_scene_table.insert(key+"_"+sub_key,[=](ImageScene& record){
                record={key,sub_key,px,py,sx,sy,r,z};
            });
        }
    }
    void save_scene(){
        std::ostringstream oss;
        oss << "image_scene={\n";
        image_scene_table.select_all([&](ImageScene& record){
            oss<<"\t{\n\t\t\""<<record.key<<"\",\n\t\t\""<<record.sub_key
            <<"\",\n\t\t"<<std::fixed << std::setprecision(1)<<record.px
            <<","<<record.py<<","<<record.sx<<","<<record.sy<<","<<record.r<<","<<record.z<<"\n\t},\n";
        });
        oss << "\n}";
        std::ofstream outputFile("C:/Users/21wyc/Documents/Project/SimpleEngine/assets/Script/data/image_scene.lua");
        if (!outputFile.is_open()) {
            std::cerr << "Error: Unable to open the file." << std::endl;
            return; // 退出程序，表示出错
        }
        outputFile << oss.str();
        outputFile.close();
    }
};