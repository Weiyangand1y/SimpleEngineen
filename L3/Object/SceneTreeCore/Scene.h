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
    std::vector<SceneNode*> free_queue;
public:
    Application* app;
    Viewport* default_viewport;
    Camera* default_camera;
    SceneNode* root_node;
    Scene(Application* p_app);
    void make_enter_scene(SceneNode* scene_node);
    void* handle_requst(std::string what, void* data);
    void add_to_root_node(SceneNode* scene_node);
    
    void add_free_node(SceneNode* node);
    void do_queue_free();

    template<typename T, typename...Args>
    T* create_scene_node(Args... args);
    template<typename T>
    T* create_scene_node();
protected:
    void add_handler(std::string key, std::function<void*(void*)> handler);
};

template <typename T, typename...Args>
inline T* Scene::create_scene_node(Args... args) {
    T* node=new T(args...);
    make_enter_scene(node);
    return node;
}
template <typename T>
inline T* Scene::create_scene_node() {
    T* node=new T();
    make_enter_scene(node);
    return node;
}
