#include "TextureDB.h"
#include "L1/App/Config.h"
#include <assert.h>
void TextureDB::init() {
    Config::getInstance().
        do_for_kv_list("image_path",[&](std::string key,std::string path){
            db[key]=Texture(path);
    });
}

TextureDB::TextureDB() {
}

Texture* TextureDB::load(std::string name, std::string file_path,std::string* message) {
    if(db.find(name)!=db.end())return &db[name];//让key值不覆盖
    //也许可以覆盖并删除原有的
    db[name]=Texture(file_path,message);
    return &db[name];
}

void TextureDB::unload(std::string name) {
    db.erase(name);
}

Texture& TextureDB::get_texture(std::string name) {
    if(db.find(name)==db.end()){
        std::cout<<name<<std::endl;
        assert(false);
    }
    return db[name];
}

Texture& TextureDB::operator[](std::string name) {
    return get_texture(name);
}

void TextureDB::add(const std::string& name, Texture& texture) {
    db[name]=texture;
}
