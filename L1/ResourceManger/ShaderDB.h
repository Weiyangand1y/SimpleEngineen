#pragma once
#include <unordered_map>
#include <string>
#include "L1/Lib/OpengL/Shader.h"
class ShaderDB{
private:
    std::unordered_map<std::string,Shader> shader_db;
public:
    ShaderDB();
    void init();
    void load_from_file(std::string name,const std::string& file_path, const std::string& file_path2);
    void load_from_text(std::string name,const std::string& vert, const std::string& frag);
    void unload(std::string name);
    Shader& get_shader(std::string name);
};