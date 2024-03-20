#pragma once
#include "L1/App/Config.h"
#include "L1/App/Application.h"
#include "Viewport.h"
#include "Camera.h"

#include "SceneNode.h"
#include "DrawableNode.h"
class SceneNode;
class Scene{
private:
    std::unordered_map<std::string, std::function<void*(void*)>> handlers;
public:
    Application* app;
    Viewport* default_viewport;
    Camera* default_camera;
    SceneNode* root_node;
    Scene(Application* p_app);
    void let_node_know_scene(SceneNode* scene_node);
    void* handle_requst(std::string what, void* data);
    template<typename T>
    T* create_scene_node();
protected:
    void add_handler(std::string key, std::function<void*(void*)> handler);
};

template <typename T>
inline T* Scene::create_scene_node() {
    T* node=new T();
    let_node_know_scene(node);
    return node;
}
