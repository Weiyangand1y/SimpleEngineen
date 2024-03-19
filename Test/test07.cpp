#include "L1/Debug/Log.h"
#include "L1/App/Application.h"

#include "L3/Object/SceneTreeCore/Scene.h"
#include "L3/Object/SceneTreeCore/Sprite2D.h"

#include "L3/Object/Physics/PhysicWorld.h"
#include "L3/Object/Physics/PhysicObject.h"

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
        po=new PhysicObject();
        pw.create_object(po);

    }
    void _run()override{
        Sprite2D* s=(Sprite2D*)scene->root_node->get_Child("@Sprite2D");
        s->set_position(po->get_position_x(),po->get_position_y());
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