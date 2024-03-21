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

    let_node_know_scene(root_node);
}


void Scene::let_node_know_scene(SceneNode* scene_node) {
    debug("Scene::add_node\n");
    scene_node->create_from_scene(this);
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
