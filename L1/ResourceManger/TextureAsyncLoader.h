#pragma once
#include <thread>
#include <functional>
#include <queue>
#include "TextureDB.h"
class TextureAsyncLoader{
public:
    struct KeyPath{
        std::string key;
        std::string path;
    };
    struct ImageData{
        std::string key;
        unsigned char* data;
        int w,h,c;
    };
    std::function<void(Texture* texture,const std::string&,float)> one_done_callback=nullptr;
    std::function<void(void)> all_done_callback=nullptr;
    TextureAsyncLoader(); 
    ~TextureAsyncLoader();
    void set_texture_db(TextureDB* p_texure_db);
    void add_task(const std::string& key, const std::string& path);
    void start_loading();
    //在主线程的循环里调用
    void load_gl_texture();
private:
    TextureDB* texture_db;
    std::queue<KeyPath> task_queue;
    std::queue<ImageData> image_queue;
    std::thread thread;
    bool finished=false;
};


