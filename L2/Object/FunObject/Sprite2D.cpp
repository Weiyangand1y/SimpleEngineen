#include "Sprite2D.h"
#include <random>
#include <vector>
void Sprite2D::_move(float px, float py) {
    x+=px;
    y+=py;
}
void Sprite2D::_rotate(float y) {
    rotation+=y;
}
Sprite2D::Sprite2D() {
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_real_distribution<float> dist(-1.0, 1.0); 
    std::vector<float> result(5);
    for (int i = 0; i < 5; ++i) {
        float random_num = dist(gen);
        result[i]=random_num;
    }
    x=result[0];y=result[1];
    //sx=result[2];sy=result[3];
    rotation=result[4];
}


mat4 Sprite2D::get_transform_mat4() {
    mat4 t(1.f);
    t=scale(t,vec3(sx,sy,1.f));
    t=rotate(t,radians(rotation),vec3(0.f,0.f,1.f));
    t=translate(t,vec3(x,y,0.f));
    return t;
}
