#pragma once
#include "L1/Object/Node.h"
#include "L1/Object/SignalObject.h"
class Scene;
class Viewport;
using SignalRecode = std::vector<std::tuple<SignalObject*,std::string,int>>;
class SceneNode : public Node{
private:
    enum State{run,stop};
    State state;
protected:
    Scene* scene;
    Viewport* viewport=nullptr;
    void serialize();
    void deserialize();
public:
    const char* class_name="SceneNode";
    SignalObject signal;
    SignalRecode signal_record;
    virtual void enter_scene(Scene* scene);
    virtual void add_child(SceneNode* node);
    //为了传viewport，一些不需要用到viewport的node也需要viewport
    void set_viewport(Viewport* p_viewport);
    virtual void before_free();
    void queue_free();
    void get_all_children(std::vector<SceneNode*>& result);
    void get_children(std::vector<SceneNode*>& result);
    SceneNode* get_child(int index);
    void make_signal_record(SignalObject& so,std::string name,int id);
    void connect_signal(SignalObject& so,std::string signal_name,Callback func);
    Scene* get_scene();
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
