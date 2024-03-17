#pragma once
#include <unordered_map>
#include <string>
#include <L1/Lib/OpengL/Texture.h>
class TextureDB{
private:
    std::unordered_map<std::string,Texture> db;
public:
    TextureDB();
    void init();
    void load(std::string name,std::string file_path);
    void unload(std::string name);
    Texture& get_texture(std::string name);
    Texture& operator[](std::string name);
};