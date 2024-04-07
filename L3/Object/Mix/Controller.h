#include "L3/Object/Mix/PhysicNode.h"
class PhysicNodeController{    
    PhysicNode* body=nullptr;
public:
    PhysicNodeController(PhysicNode* pn):body(pn){

    }
    void connect_signal(SignalObject& s){
        s.connect("left",[&](const Info&){
            body->add_impulse(-10.f,0.f);
        });
        s.connect("right",[&](const Info&){
            body->add_impulse(10.f,0.f);
        });
        s.connect("up",[&](const Info&){
            body->add_impulse(0.f,10.f);
        });
        s.connect("down",[&](const Info&){
            body->add_impulse(0.f,-10.f);
        });
    }
};