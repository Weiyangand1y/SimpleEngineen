#include "L1/Debug/Log.h"
#include "L1/App/Application.h"

#include "L3/Object/SceneTreeCore/Scene.h"
#include "L3/Object/SceneTreeCore/Sprite2D.h"

class L3App : public Application{
Scene* scene;
public:
    void _init()override{
        scene=new Scene(this);

        // DrawableNode* dn=new DrawableNode();
        // scene->let_node_know_scene(dn);
        // scene->root_node->addChild(dn);
        // dn->set_viewport(scene->default_viewport);

        Sprite2D* sp=new Sprite2D();
        scene->let_node_know_scene(sp);
        sp->set_texture("Pippi_Carter");
        scene->root_node->add_child(sp);
    }
    void _run()override{
        scene->root_node->_process(delta_time);
        scene->root_node->_after_process(delta_time);
    }
};
int main(){
    system("cls");
    L3App app;
    app.init();
    app.run();
}