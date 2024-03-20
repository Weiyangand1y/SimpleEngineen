#include "ShaderDB.h"
#include "L1/App/Config.h"
#include "L1/Lib/IO/TextLoader.h"
#include <assert.h>
ShaderDB::ShaderDB() {}

void ShaderDB::init() {
    std::string base_path=Config::getInstance().get("shader_base_path");
    std::string very_simple_v=loadTextFile(base_path+"very_simple.vert");
    std::string very_simple_f=loadTextFile(base_path+"very_simple.frag");
    std::string simple_texture_v=loadTextFile(base_path+"simple_texture.vert");
    std::string simple_texture_f=loadTextFile(base_path+"simple_texture.frag");
    std::string simple_color_f=loadTextFile(base_path+"simple_color.frag");
    std::string can_transform_v=loadTextFile(base_path+"transform.vert");
    std::string screen_texture_f=loadTextFile(base_path+"screen_texture.frag");

    shader_db["very_simple"]=Shader(very_simple_v,very_simple_f);
    shader_db["can_transform"]=Shader(can_transform_v,very_simple_f);
    shader_db["color_transform"]=Shader(can_transform_v,simple_color_f);
    shader_db["rect_texture"]=Shader(simple_texture_v,simple_texture_f);
    shader_db["screen"]=Shader(simple_texture_v,screen_texture_f);
}

void ShaderDB::load_from_file(std::string name,const std::string& file_path1,const std::string& file_path2) {
    shader_db[name]=Shader(
        loadTextFile(file_path1),
        loadTextFile(file_path2)
    );
}

void ShaderDB::load_from_text(std::string name,const std::string& vert,const std::string& frag) {
    shader_db[name]=Shader(vert,frag);
}

void ShaderDB::unload(std::string name) {
    shader_db.erase(name);
}

Shader& ShaderDB::get_shader(std::string name) {
    if(shader_db.find(name)==shader_db.end()){
        std::cout<<"!!!no the shader!!!"<<name<<std::endl;
        assert(false);
    }
    return shader_db[name];
}
