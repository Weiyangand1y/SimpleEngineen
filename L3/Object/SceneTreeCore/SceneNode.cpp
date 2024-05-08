#include "SceneNode.h"
#include "Scene.h"
#include "L1/Debug/Log.h"
#include "Viewport.h"
void SceneNode::enter_scene(Scene* p_scene) {
    scene=p_scene;
}

void SceneNode::add_child(SceneNode* node) {
    assert(viewport);
    node->viewport=viewport;
    addChild(node);    
}

void SceneNode::set_viewport(Viewport* p_viewport) {
    viewport=p_viewport;
}

void SceneNode::before_free() {
    parent->remove_child(this);
    for(auto [so,name,id]:signal_record){
        so->disconnect(name,id);
    }
}

void SceneNode::queue_free() {
    scene->add_free_node(this);
}

void SceneNode::get_all_children(std::vector<SceneNode*>& result) {
    for (Node* child : children) {
        result.push_back(static_cast<SceneNode*>(child));
        if(!children.empty())
            static_cast<SceneNode*>(child)->get_all_children(result);
    }
}

void SceneNode::make_signal_record(SignalObject& so, std::string name, int id) {
    signal_record.push_back({&so,name,id});
}

void SceneNode::connect_signal(SignalObject& so,std::string signal_name,Callback func) {
    int id=so.connect(signal_name,func);
    make_signal_record(so,signal_name,id);
}
