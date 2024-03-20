#include "Node.h"
Node* Node::get_Child(const std::string& name) {
    if(children_cache.find(name)==children_cache.end())
        return nullptr;
    return children_cache[name];
}
void Node::addChild(Node* node) {
    children.push_back(node);
    node->ready();
    node->parent=this;
    if(children_cache.find(node->name)!=children_cache.end()){
        char last_char=node->name.back();
        if(last_char>='0' && last_char<'9')
            node->name.back()=last_char+1;
        else
            node->name+='0';
    }
    children_cache[node->name]=node;
}
void Node::removeChild(Node* node) {
    children.erase(std::remove(children.begin(), children.end(), node),
                   children.end());
    children_cache.erase(node->name);
}

void Node::ready() {
    std::cout << name << " is ready" << std::endl;
}

void Node::process(float delta) {}

Node::Node(std::string p_name) {
    name = p_name;
    ready();
}


void Node::_process(float delta) {
    process(delta);
    for (Node* child : children) {
        child->_process(delta);
    }
}

void Node::after_process(float delta) {}

void Node::_after_process(float delta) {
    after_process(delta);
    for (Node* child : children) {
        child->_after_process(delta);
    }
}

void Node::set_name(std::string p_name) {
    name=p_name;
}

Node::Node() {
    ready();
}

