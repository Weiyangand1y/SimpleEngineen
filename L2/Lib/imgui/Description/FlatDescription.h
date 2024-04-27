#pragma once
#include "../MyImGui.h"
struct Color{
    float r=1.f,g=1.f,b=1.f,a=1.f;
    Color(float p_r,float p_g,float p_b,float p_a=1.f){
        r=p_r;g=p_g;b=p_b;a=p_a;
    }
    Color(){
        
    }
    static Color from_hex8(uint32_t p_hex){
        float a = (p_hex & 0xFF) / 255.0f;
        p_hex >>= 8;
        float b = (p_hex & 0xFF) / 255.0f;
        p_hex >>= 8;
        float g = (p_hex & 0xFF) / 255.0f;
        p_hex >>= 8;
        float r = (p_hex & 0xFF) / 255.0f;
        return Color(r, g, b, a);
    }
    static Color from_hex6(uint32_t p_hex){
        float b = (p_hex & 0xFF) / 255.0f;
        p_hex >>= 8;
        float g = (p_hex & 0xFF) / 255.0f;
        p_hex >>= 8;
        float r = (p_hex & 0xFF) / 255.0f;
        return Color(r, g, b, 1.f);
    }
    void from_rgba256(){

    }
    int to_imgui_color(){
        return IM_COL32(r*255,g*255,b*255,a*255);
    }

};
struct PresetColor{
    struct Orange{
        static Color d50(){return Color::from_hex8(0xfff7edff);}
        static Color d500(){return Color::from_hex6(0xf97316);}
    };
    struct Red{
        static Color d500(){return Color::from_hex6(0xef4444);}
    };
};
struct FlatDescription{
    
    struct BorderDecription{
        float thickness=1.f;
        float r=10.f;
        Color color;
        BorderDecription(){
            color=PresetColor::Orange::d500();
        }       
    };
    struct ColorDecription{
        Color background;
        Color font_color;
    };
    struct StateDecription{
        BorderDecription border;
        ColorDecription color;
        ImVec2 size={0,0};
        ImVec2 frame_padding={5,5};
    };
    StateDecription normal;
    StateDecription hover;
    StateDecription hold;
};
