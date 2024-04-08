#include "Node.h"
#include "L1/Debug/Log.h"
Node* Node::get_Child(const std::string& name) {
    if(children_cache.find(name)==children_cache.end())
        return nullptr;
    return children_cache[name];
}
void Node::addChild(Node* node) {
    children.push_back(node);   
    node->parent=this;
    if(children_cache.find(node->name)!=children_cache.end()){
//        debug("{} is collision name\n",node->name);
        node->name.append(std::to_string(children.size()));
    }
    children_cache[node->name]=node;
    node->ready();
}
void Node::removeChild(Node* node) {
    children.erase(std::remove(children.begin(), children.end(), node),
                   children.end());
    children_cache.erase(node->name);
}

void Node::ready() {
//    debug("{} is ready\n",name);
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

