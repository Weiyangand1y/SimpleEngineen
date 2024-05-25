#include "L1/Debug/Log.h"
#include "L1/App/Application.h"

#include "L3/Object/SceneTreeCore/Scene.h"
#include "L3/Object/SceneTreeCore/Sprite2D.h"
#include "L1/Object/ScriptObject.h"
#include "L3/Object/Mix/ScriptBind.h"
void save_node(SceneNode* node,int& index){
    std::unordered_map<std::string, std::function<void()>> db;
    db["Node2D"]=[node,index]{
        auto node2d=reinterpret_cast<Node2D*>(node);
        float x=node2d->m_position.x;
        float y=node2d->m_position.y;
        std::string str = fmt::format(
            "n{}=add_node2d()\n"
            "n{}:set_position({},{})",
            index,index,
            x ,y
            );
        Logger::log(2,str);
    };
    std::string class_name=std::string(node->class_name);
    auto call_function=db[class_name];
    if(call_function){
        call_function();
    }else{
        Logger::log(8,"unregistered class");
    }
    std::vector<SceneNode*> v;
    node->get_children(v);
    int original_index=index;
    for(auto n:v){
        index++;
        save_node(n,index);
        std::string str = fmt::format("n{}:add_child(n{})",original_index,index);
        Logger::log(2,str);
    }

}
void save_all(SceneNode* node){
    int index=0;
    save_node(node,index);


}
void load(SceneNode* node){
    ScriptObject so;
    script_bind_class(so.script);
    so.script["add_node2d"]=[node](){       
        return node->create_add_child<Node2D>();
    };
    so.script.do_string(
        "n1=add_node2d()\n"
        "n1:set_name('hello')"
        "n1:set_position(3,1)"
        );
}
class L3App : public Application{
Scene* scene;
public:
    void _init()override{
        
        
        scene=new Scene(this);
        Sprite2D* sp=scene->root_node->create_add_child<Sprite2D>();
        sp->set_texture("js");
        debug("class name: {}\n",sp->class_name);
        Node2D* n2=scene->root_node->create_add_child<Node2D>();
        Node2D* n3=n2->create_add_child<Node2D>();
        n2->create_add_child<Node2D>();
        debug("class name: {}\n",n2->class_name);
        sp->add_child(n2);
        debug("path: {}\n",n3->get_path());

        n2->set_position(3.f,1.f);
        save_all(n2);

        load(n2);
        std::vector<SceneNode*> v;
        n2->get_all_children(v);
        debug("__{}\n",v.size());
        int i=0;
        for(auto n:v){
            debug("{}, {}\n",i++,n->get_name());

        }
        Node* n=n2->get_child("hello");
        
        if(n)debug("find~~\n");





        // Node* n1=new Node("n1");
        // Node* n2=new Node("n2");
        // Node* n3=new Node("n3");
        // Node* n4=new Node("n4");
        // Node* n5=new Node("n51");

        // n1->addChild(n2);
        // n1->addChild(n3);

        // n2->addChild(n4);
        // n2->addChild(n5);

        // Node* n01=n1->get_child_by_path("n2/n4");
        // debug("n01: {}\n",n01->get_name());
        // Node* n02=n2->get_child_by_path("n51");
        // debug("n02: {}\n",n02->get_name());
        // debug("path: {}\n",n02->get_path());
        


    }
    void _run()override{
        scene->run(delta_time);
        drawer.draw_texture(renderer.get_framebuffer_color_texture_id());
    }
};
int main(){
    system("cls");
    L3App app;
    app.init();
    app.run();
}