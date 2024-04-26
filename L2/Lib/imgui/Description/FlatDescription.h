#pragma once
struct Color{
    float r=0.f,g=0.f,b=0.f,a=1.f;
    Color(float p_r,float p_g,float p_b,float p_a){
        *this={p_r,p_g,p_b,p_a};
    }
    static Color from_hex(uint32_t p_hex){
        float a = (p_hex & 0xFF) / 255.0f;
        p_hex >>= 8;
        float b = (p_hex & 0xFF) / 255.0f;
        p_hex >>= 8;
        float g = (p_hex & 0xFF) / 255.0f;
        p_hex >>= 8;
        float r = (p_hex & 0xFF) / 255.0f;
        return Color(r, g, b, a);
    }
    void from_rgba256(){

    }
    int to_imgui_color(){
        return 0;
    }

};
struct PresetColor{
    struct Orange{
        static Color d50(){ }
    };
};
struct FlatDescription{
    
    struct BorderDecription{
        float thickness=1.f;
        float r=0.f;
        Color color;       
    };
    struct ColorDecription{
        Color background;
        Color font_color;
    };
    struct StateDecription{
        BorderDecription border;
        ColorDecription color;
    };
    StateDecription normal;
    StateDecription hover;
    StateDecription hold;
};
