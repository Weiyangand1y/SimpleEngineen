#include "L1/Debug/Log.h"
#include "L1/App/Application.h"

#include "L3/Object/SceneTreeCore/Scene.h"
#include "L3/Object/SceneTreeCore/Sprite2D.h"
#include "L1/Object/ScriptObject.h"
#include "L3/Object/Mix/ScriptBind.h"
void save_node(SceneNode* node,int& index,int parent_index,std::stringstream& ss){
    std::unordered_map<std::string, std::function<void()>> db;
    db["Node2D"]=[node,index,&ss](){
        auto node2d=reinterpret_cast<Node2D*>(node);
        float x=node2d->m_position.x;
        float y=node2d->m_position.y;
        std::string str = fmt::format(
            "n{}=add_node2d();  "
            "n{}:set_position({},{});  "
            "n{}:set_name('{}')",
            index,
            index,x ,y,
            index,node2d->get_name()
            );
        Logger::log(2,str);
        ss<<str<<"\n";
    };
    db["Sprite2D"]=[node,index,&ss](){
        auto sprite2d=reinterpret_cast<Sprite2D*>(node);
        float x=sprite2d->m_position.x;
        float y=sprite2d->m_position.y;
        std::string str = fmt::format(
            "n{}=add_sprite2d();  "
            "n{}:set_position({},{});  "
            "n{}:set_texture('{}');   "
            "n{}:set_name('{}')",
            index,
            index,x ,y,
            index,std::string(sprite2d->texture_key),
            index,sprite2d->get_name()
            );
        Logger::log(2,str);
        ss<<str<<"\n";
    };
    std::string class_name=std::string(node->class_name);
    auto call_function=db[class_name];
    if(call_function){
        call_function();
        if(parent_index>=0){
            std::string str = fmt::format("n{}:add_child(n{})",parent_index,index);
            Logger::log(2,str);
            ss<<str<<"\n";
        }
        else{
            std::string str = fmt::format("attach(n{})",index);
            Logger::log(2,str);
            ss<<str<<"\n";
        }
    }else{
        Logger::log(8,"unregistered class");
    }
    std::vector<SceneNode*> v;
    node->get_children(v);
    int original_index=index;
    for(auto n:v){
        index++;
        save_node(n,index,original_index,ss);
    }

}
std::string save_all(SceneNode* node){
    std::stringstream ss;
    int index=0;
    save_node(node->get_child(0),index,-1,ss);
    return ss.str();
}
void load(SceneNode* node,const std::string& content){
    ScriptObject so;
    script_bind_class(so.script);
    so.script["add_node2d"]=[node](){       
        return node->get_scene()->create_scene_node<Node2D>();
    };
    so.script["add_sprite2d"]=[node](){       
        return node->get_scene()->create_scene_node<Sprite2D>();
    };
    so.script["attach"]=[node](SceneNode* n0){
        node->add_child(n0);
    };
    //
    so.script.do_string(content);
}
class L3App : public Application{
Scene* scene;
public:
    void _init()override{       
        scene=new Scene(this);
        auto n1=scene->root_node->create_add_child<Node2D>();
        n1->set_name("n1");
        n1->set_position(100,0);
        auto n2=n1->create_add_child<Sprite2D>();
        n2->set_name("p1");
        n2->set_texture("p1");
        std::string save_data =  save_all(scene->root_node);
        Logger::log(8,save_data);
        scene->root_node->print_child_as_tree();
        scene->root_node->get_child(0)->queue_free();
        scene->do_queue_free();
        load(scene->root_node,save_data);
        scene->root_node->print_child_as_tree();
        Node* n2d=scene->root_node->get_child_by_path("n1");
        Node2D* node2d=static_cast<Node2D*>(n2d);
        debug("node2d pos: {} {}\n",node2d->m_position.x,node2d->m_position.y);

    }
    void _run()override{
        scene->run(delta_time);
        drawer.draw_texture(renderer.get_framebuffer_color_texture_id());
    }
};
int main(){
    system("cls");
    system("chcp 65001");
    L3App app;
    app.init();
    app.run();
}