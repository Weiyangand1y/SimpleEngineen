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
    Texture* load(std::string name,std::string file_path,std::string* message=nullptr);
    void unload(std::string name);
    Texture& get_texture(std::string name);
    Texture& operator[](std::string name);
    void add(const std::string& name,Texture& texture);
};