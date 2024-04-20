#pragma once
#include "L2/Lib/imgui/MyImGui.h"
#include <string>
namespace ImagePlatterType
{
    struct Transform{
        ImVec2 position={350,150};
        ImVec2 size={-1,-1};
        float rotation=0.f;
        int z_index=0;
    };
    struct UnitData{
        int id;
        std::string key;
        std::string sub_key;
        int texture_id;
        Transform transform;
        float left=0.f,right=1.f,top=1.f,bottom=0.f;//uv
    };
    struct ZindexPair{
        int z_index;
        int id;
    };
}; // namespace ImagePlatter

