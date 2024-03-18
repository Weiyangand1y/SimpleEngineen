#include "Node.h"
void Node::addChild(Node* node) {
    children.push_back(node);
    node->ready();
    node->parent=this;
}
void Node::removeChild(Node* node) {
    children.erase(std::remove(children.begin(), children.end(), node),
                   children.end());
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

Node::Node() {
    ready();
}

