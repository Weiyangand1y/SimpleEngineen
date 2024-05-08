#pragma once
//normal rect
struct Rect{
    float x;
    float y;
    float w;
    float h;
};
struct UVs{
    float left,right;
    float bottom,top;
};
//rect can rotate
struct RRect{
    float x,y;
    float w,h;
    float rotation=0.f;
};

