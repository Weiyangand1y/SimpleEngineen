#pragma once
#include "L2/Object/MyDataBase.h"
#include <sstream>
#include <fstream>
#include <iomanip>
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
    };
    MyDatabase<MainTexture> main_texture_table;
    MyDatabase<SubTexture> sub_texture_table;
    void insert_main_texture(std::string key,int texture_id,float aspect_radio=1.f,std::string path=""){
        main_texture_table.insert([=](MainTexture& record){
            record={key,texture_id,aspect_radio,path};
        });
    }
    void insert_sub_texture(std::string subkey,std::string key,int texture_id,
                    float left,float right,float top,float bottom,float aspect_radio=1.f){
            sub_texture_table.insert([=](SubTexture& record){
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