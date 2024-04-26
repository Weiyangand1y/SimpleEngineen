#include "TextureAsyncLoader.h"
#include "L1/Lib/IO/ImageLoader.h"
TextureAsyncLoader::TextureAsyncLoader() {
    
}

TextureAsyncLoader::~TextureAsyncLoader() {
    
}

void TextureAsyncLoader::set_texture_db(TextureDB* p_texure_db) {
    texture_db=p_texure_db;
}

void TextureAsyncLoader::add_task(const std::string& key,const std::string& path) {
    task_queue.push({key,path});
}

void TextureAsyncLoader::start_loading() {
    thread=std::thread([&](){
        size_t size=task_queue.size();
        for (size_t i = 0; i < size; i++){
            auto& [key,path]=task_queue.front();
            int w,h,c;
            ImageLoader loader;
            unsigned char* data = loader.loadImage(path.c_str(),&w,&h,&c);
            image_queue.push(ImageData{key,data,w,h,c});            
            task_queue.pop();
        }
    });
    thread.detach();
}

void TextureAsyncLoader::load_gl_texture() {
    if(finished)return;
    size_t size=image_queue.size();
    for (size_t i = 0; i < size; i++){
        auto& image=image_queue.front();
        texture_db->add(image.key,Texture(image.data,image.w,image.h,image.c));        
        if(one_done_callback)one_done_callback(&texture_db->get_texture(image.key),image.key,0.f);        
        image_queue.pop();
    }    
    if(task_queue.size()==0 && image_queue.size()==0 &&all_done_callback){
        all_done_callback();
        finished=true;
    }
}
