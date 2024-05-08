#include "L1/Debug/Log.h"
#include "L1/App/Application.h"

#include "L3/Object/SceneTreeCore/Scene.h"
#include "L3/Object/SceneTreeCore/Sprite2D.h"

class L3App : public Application{
Scene* scene;
public:
    void _init()override{
        scene=new Scene(this);
        Sprite2D* sp=scene->root_node->create_add_child<Sprite2D>();
        sp->set_texture("p1");

        Node* n1=new Node("n1");
        Node* n2=new Node("n2");
        Node* n3=new Node("n3");
        Node* n4=new Node("n4");
        Node* n5=new Node("n51");

        n1->addChild(n2);
        n1->addChild(n3);

        n2->addChild(n4);
        n2->addChild(n5);

        Node* n01=n1->get_child_by_path("n2/n4");
        debug("n01: {}\n",n01->get_name());
        Node* n02=n2->get_child_by_path("n51");
        debug("n02: {}\n",n02->get_name());
        debug("path: {}\n",n02->get_path());
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