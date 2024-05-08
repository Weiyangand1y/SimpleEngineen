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
    static Color white(){return Color::from_hex6(0xffffff);}
    static Color black(){return Color::from_hex6(0x0);}
    struct Orange{
        static Color d50()  {return Color::from_hex6(0xfff7ed);}
        static Color d100() {return Color::from_hex6(0xffedd5);}
        static Color d200() {return Color::from_hex6(0xfed7aa);}
        static Color d300() {return Color::from_hex6(0xfdba74);}
        static Color d400() {return Color::from_hex6(0xfb923c);}
        static Color d500() {return Color::from_hex6(0xf97316);}
        static Color d600() {return Color::from_hex6(0xea580c);}
        static Color d700() {return Color::from_hex6(0xc2410c);}
        static Color d800() {return Color::from_hex6(0x9a3412);}
        static Color d900() {return Color::from_hex6(0x7c2d12);}
        static Color d950() {return Color::from_hex6(0x431407);}       
    };
    struct Red{
        static Color d500(){return Color::from_hex6(0xef4444);}
    };
    struct Green{
        static Color d50()  {return Color::from_hex6(0xf0fdf4);}
        static Color d100() {return Color::from_hex6(0xdcfce7);}
        static Color d200() {return Color::from_hex6(0xbbf7d0);}
        static Color d300() {return Color::from_hex6(0x86efac);}
        static Color d400() {return Color::from_hex6(0x4ade80);}
        static Color d500() {return Color::from_hex6(0x22c55e);}
        static Color d600() {return Color::from_hex6(0x16a34a);}
        static Color d700() {return Color::from_hex6(0x15803d);}
        static Color d800() {return Color::from_hex6(0x166534);}
        static Color d900() {return Color::from_hex6(0x14532d);}
        static Color d950() {return Color::from_hex6(0x052e16);}
    };
    struct Cyan{
        static Color d50() {return Color::from_hex6(0xecfeff);}
        static Color d100() {return Color::from_hex6(0xcffafe);}
        static Color d200() {return Color::from_hex6(0xa5f3fc);}
        static Color d300() {return Color::from_hex6(0x67e8f9);}
        static Color d400() {return Color::from_hex6(0x22d3ee);}
        static Color d500() {return Color::from_hex6(0x06b6d4);}
        static Color d600() {return Color::from_hex6(0x0891b2);}
        static Color d700() {return Color::from_hex6(0xe7490);}
        static Color d800() {return Color::from_hex6(0x155e75);}
        static Color d900() {return Color::from_hex6(0x164e63);}
        static Color d950() {return Color::from_hex6(0x083344);}
    };
    struct Rose{
        static Color d50()  {return Color::from_hex6(0xfff1f2);}
        static Color d100() {return Color::from_hex6(0xffe4e6);}
        static Color d200() {return Color::from_hex6(0xfecdd3);}
        static Color d300() {return Color::from_hex6(0xfda4af);}
        static Color d400() {return Color::from_hex6(0xfb7185);}
        static Color d500() {return Color::from_hex6(0xf43f5e);}
        static Color d600() {return Color::from_hex6(0xe11d48);}
        static Color d700() {return Color::from_hex6(0xbe123c);}
        static Color d800() {return Color::from_hex6(0x9f1239);}
        static Color d900() {return Color::from_hex6(0x881337);}
        static Color d950() {return Color::from_hex6(0x4c0519);}
    };
    struct Blue{
        static Color d50() {return Color::from_hex6(0xeff6ff);}
        static Color d100() {return Color::from_hex6(0xdbeafe);}
        static Color d200() {return Color::from_hex6(0xbfdbfe);}
        static Color d300() {return Color::from_hex6(0x93c5fd);}
        static Color d400() {return Color::from_hex6(0x60a5fa);}
        static Color d500() {return Color::from_hex6(0x3b82f6);}
        static Color d600() {return Color::from_hex6(0x2563eb);}
        static Color d700() {return Color::from_hex6(0x1d4ed8);}
        static Color d800() {return Color::from_hex6(0x1e40af);}
        static Color d900() {return Color::from_hex6(0x1e3a8a);}
        static Color d950() {return Color::from_hex6(0x172554);}
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
