#include "ImageDB.h"
#include <sstream>
#include <fstream>
#include <iomanip>
#include "L1/Render/Renderer.h"
#include "L1/App/Config.h"
#include "L1/Debug/TimeMeasure.h"
void ImageDB::set_renderer(Render* p_renderer){
    renderer=p_renderer;
    texture_async_loader.set_texture_db(&renderer->get_texture_db());
}

void ImageDB:: async_load_image(){
    ScriptObject so;
    so.execute(Config::getInstance().get("lua_script_file")+"/data/image2.lua");
    sol::table image_list=so.script["main_images"];
    for(auto& r:image_list){
        sol::table& imageTable = r.second.as<sol::table>();
        std::string name = imageTable[1];
        std::string path = imageTable[2];
        insert_main_texture(name,-1,-1,path);
        texture_async_loader.add_task(name,path);
    }
    for (int i = 0; i < 100; i++){
        texture_async_loader.add_task("sth"+std::to_string(i),"C:/Users/21wyc/Pictures/pixel/117601008_p0.png");
    }
    

    sol::table sub_image_list=so.script["sub_images"];
    for(auto& r:sub_image_list){
        sol::table& imageTable = r.second.as<sol::table>();
        std::string subkey = imageTable[1];
        std::string key = imageTable[2];
        float left=imageTable[3];
        float right=imageTable[4];
        float top=imageTable[5];
        float bottom=imageTable[6];
        insert_sub_texture(subkey,key,-1,left,right,top,bottom,-1);
    }
    texture_async_loader.one_done_callback=[&](Texture* t, const std::string& key,float){
        //update Main
        MainTexture* main_texture=main_texture_table.select_by_key(key);
        if(!main_texture)return;
        main_texture->texture_id=t->get_id();
        main_texture->aspect_ratio=t->get_aspect_ratio();
        //update Sub
        sub_texture_table.update_where(
        [=](SubTexture& record){
            return record.key==key;
        },
        [=](SubTexture& record){                               
            record.texture_id=t->get_id();
            record.aspect_ratio=t->get_aspect_ratio();
        }
        );
        signal.emit("one_finish");
    };
    texture_async_loader.all_done_callback=[&](){
        signal.emit("load_finish",Info());
    };
    texture_async_loader.start_loading();
}
void ImageDB:: load_from_file(){
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
void ImageDB:: insert_main_texture(std::string key,int texture_id,float aspect_radio,std::string path){
    main_texture_table.insert(key,[=](MainTexture& record){
        record={key,texture_id,aspect_radio,path};
    });
}
void ImageDB:: insert_sub_texture(std::string subkey,std::string key,int texture_id,
                float left,float right,float top,float bottom,float aspect_radio){
        sub_texture_table.insert(subkey,[=](SubTexture& record){
        record={subkey,key,texture_id,left,right,top,bottom,aspect_radio};
    });
}
void ImageDB:: save_to_file(){
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
void ImageDB:: load_scene_from_file(){
    ScriptObject so;
    so.execute(Config::getInstance().get("lua_script_file")+"/data/image_scene.lua");
    sol::table image_list=so.script["image_scene"];
    int i=0;
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
        image_scene_table.insert(key+"_"+sub_key+std::to_string(i++),[=](ImageScene& record){
            record={key,sub_key,px,py,sx,sy,r,z};
        });
    }
}
void ImageDB:: save_scene(){
    std::ostringstream oss;
    oss << "image_scene={\n";
    image_scene_table2.select_all([&](ImageScene& record){
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

void ImageDB::update() {
    texture_async_loader.load_gl_texture();
}

