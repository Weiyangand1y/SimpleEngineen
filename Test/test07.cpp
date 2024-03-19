#include "L1/Debug/Log.h"
#include "L1/App/Application.h"

#include "L3/Object/SceneTreeCore/Scene.h"
#include "L3/Object/SceneTreeCore/Sprite2D.h"

#include "L3/Object/Physics/PhysicWorld.h"
#include "L3/Object/Physics/PhysicObject.h"
#include "L3/Object/Mix/PhysicNode.h"
class L3App : public Application{
Scene* scene;
PhysicWorld pw;
PhysicObject* po;
public:
    void _init()override{
        scene=new Scene(this);
        Sprite2D* sp=new Sprite2D();
        scene->let_node_know_scene(sp);
        sp->set_texture("Pippi_Carter");
        scene->root_node->add_child(sp);

        //-----------------------------
        po=new PhysicObject(PhysicObject::BodyType::DYNAMIC);
        po->init_info={30,30,0,5.7,9.0};
        pw.register_object(po);
        po->update_callback=[=](float x,float y,float angle){
            sp->set_position_and_angle(x,y,angle);
        };
        po->set_init_speed(0.f,30.f);
        

        PhysicObject* go=new PhysicObject(PhysicObject::BodyType::STATIC);
        go->init_info={0,-30,0.1f,80,10};
        pw.register_object(go);
        
    }
    void _run()override{
        po->update();
        scene->root_node->_process(delta_time);
        scene->root_node->_after_process(delta_time);
        pw.run();
        //debug("pos:  {}, {}\n",po->get_position_x(),po->get_position_y());
    }
};
int main(){
    system("cls");
    L3App app;
    app.init();
    app.run();
}