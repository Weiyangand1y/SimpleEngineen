#pragma once
#include "L1/Object/Node.h"
#include "L1/Object/SignalObject.h"
class Scene;
class Viewport;
class SceneNode : public Node{
protected:
    Scene* scene;
    Viewport* viewport=nullptr;
public:
    SignalObject signal;
    virtual void enter_scene(Scene* scene);
    virtual void add_child(SceneNode* node);
    void set_viewport(Viewport* p_viewport);
    template<typename T, typename...Args>
    T* create_add_child(Args... args);
    template<typename T>
    T* create_add_child();

};

template <typename T, typename... Args>
inline T* SceneNode::create_add_child(Args... args) {
    T* node=scene->create_scene_node<T>(args...);
    add_child(node);
    return node;
}

template<typename T>
inline T * SceneNode::create_add_child(){
    T* node=scene->create_scene_node<T>();
    add_child(node);
    return node;
}
