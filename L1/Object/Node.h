#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "L1/Render/Drawer.h"

class Node {
    std::unordered_map<std::string, Node*> children_cache;
public:
    Node* get_child(const std::string& name);
    Node* get_child_by_path(const std::string& name);
    virtual void add_child(Node* node);
    void remove_child(Node* node);

    std::string get_name();
    std::string get_path();
    void print_child_as_tree(const std::string& prefix = "", bool isLast = true);

    virtual void ready();
    virtual void process(float delta);
    virtual void _process(float delta);

    virtual void after_process(float delta);
    virtual void _after_process(float delta);

    template<typename T>
    T* cast_to();

    

    void set_name(std::string p_name);

    Node(std::string p_name);
    Node();


protected:
    std::vector<Node*> children;
    Node* parent=nullptr;//if null => root
    std::string name="@node";
};

template <typename T>
inline T* Node::cast_to() {
    return dynamic_cast<T*>(this);
}
