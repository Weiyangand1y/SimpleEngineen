#include "TextureDB.h"
#include "L1/App/Config.h"
#include <assert.h>
void TextureDB::init() {
    std::string base_path=Config::getInstance().get("texture_base_path");
    db["Claudette_Huy"]=Texture(base_path+"character/Claudette_Huy.png");    
    db["Maki_Rollo"]=Texture(base_path+"character/Maki_Rollo.png");
    db["Pippi_Carter"]=Texture(base_path+"character/Pippi_Carter.png");
}

TextureDB::TextureDB() {
}

void TextureDB::load(std::string name, std::string file_path) {
    if(db.find(name)!=db.end())return;//
    db[name]=Texture(file_path);
}

void TextureDB::unload(std::string name) {
    db.erase(name);
}

Texture& TextureDB::get_texture(std::string name) {
    if(db.find(name)==db.end()){
        assert(false);
    }
    return db[name];
}

Texture& TextureDB::operator[](std::string name) {
    return get_texture(name);
}
