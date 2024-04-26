#pragma once
#include "L1/Object/ScriptObject.h"
#include "L1/Object/SignalObject.h"
#include "L1/ResourceManger/TextureAsyncLoader.h"

#include "L2/Object/MyDataBase.h"

class Render;
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
    MyDatabase<ImageScene> image_scene_table2;//to save
    Render* renderer=nullptr;
    TextureAsyncLoader texture_async_loader;
    SignalObject signal;


    void set_renderer(Render* p_renderer);

    void async_load_image();
    void load_from_file();
    void insert_main_texture(std::string key,int texture_id,float aspect_radio=1.f,std::string path="");
    void insert_sub_texture(std::string subkey,std::string key,int texture_id,
                    float left,float right,float top,float bottom,float aspect_radio=1.f);
    void save_to_file();
    void load_scene_from_file();
    void save_scene();
    void update();
};