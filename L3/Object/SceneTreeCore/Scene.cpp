#include "Scene.h"
#include "L1/Debug/Log.h"
#include <unordered_map>
#include <functional>
Scene::Scene(Application* p_app) {
    app=p_app;
    default_viewport=new Viewport();
    default_camera=new Camera();
    default_viewport->set_camera(default_camera);
    root_node=default_viewport;
    root_node->set_name("root");

    make_enter_scene(root_node);
}

void Scene::add_free_node(SceneNode* node){
    free_queue.push_back(node);
    node->get_all_children(free_queue);
}
void Scene::run(float delta_time) {
    root_node->_process(delta_time);
    root_node->_after_process(delta_time);
}
void Scene::do_queue_free() {
    for(auto c: free_queue)c->before_free();
    for(auto c: free_queue)delete c;
}

void Scene::make_enter_scene(SceneNode* scene_node) {
    Logger::log(0,"Scene::add_node");
    scene_node->enter_scene(this);
}

void Scene::add_to_root_node(SceneNode* scene_node) {
    root_node->add_child(scene_node);
}

//这个函数假定你已知道指针类型
void* Scene::handle_requst(std::string what, void* obj_data) {
    auto it = handlers.find(what);
    if (it != handlers.end()) {
        return it->second(obj_data);
    } else {
        assert(false);
    }
    return nullptr;
}

void Scene::add_handler(std::string key, std::function<void*(void*)> handler) {
    handlers[key]=handler;
}
