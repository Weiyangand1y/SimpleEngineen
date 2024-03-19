#pragma once
#include <box2d/box2d.h>
#include <functional>
class PhysicObject{
public:
    enum class BodyType {STATIC, DYNAMIC};
private:
    b2BodyDef body_def;
    b2Body* body;   
    b2PolygonShape shape;
    b2FixtureDef fixtureDef;
public:
    BodyType body_type=BodyType::DYNAMIC;
    std::function<void(float,float,float)> update_callback;
    PhysicObject(BodyType p_body_type);
    PhysicObject();
    void init(b2World* world);
    void update();
    void set_init_speed(float x,float y);
    struct InitInfo{//位置x,y, 角度，box的长宽
        float px, py, angle, sx, sy;
    };
    InitInfo init_info;
};

