#include "Node.h"
#include "L1/Debug/Log.h"
#include <stack>
Node* Node::get_child(const std::string& name) {
    debug("chidren num: {}\n",children_cache.size());
    for(auto [k,v]: children_cache){
        debug("chidren name: {}\n",k);
    }
    if(children_cache.find(name)==children_cache.end())
        return nullptr;
    return children_cache[name];
}

Node* Node::get_child_by_path(const std::string& path) {
    std::vector<std::string> split_path;
    //split path
    size_t start = 0;
    size_t pos = path.find('/');
    while (pos != std::string::npos) {
        split_path.push_back(path.substr(start, pos - start));
        start = pos + 1;
        pos = path.find('/', start);
    }
    if (start < path.length()) {
        split_path.push_back(path.substr(start));
    }
    //get node according path
    if (split_path.empty()) return nullptr;
    Node* currentNode = this;
    for (const std::string& nodeName : split_path) {
        currentNode = currentNode->get_child(nodeName);
        if (!currentNode) return nullptr;
    }
    return currentNode;
}

void Node::add_child(Node* node) {
    children.push_back(node);   
    node->parent=this;
    if(children_cache.find(node->name)!=children_cache.end()){
//        debug("{} is collision name\n",node->name);
        node->name.append(std::to_string(children.size()));
    }
    children_cache[node->name]=node;
    node->ready();
}
void Node::remove_child(Node* node) {
    children.erase(std::remove(children.begin(), children.end(), node),
                   children.end());
    children_cache.erase(node->name);
}

std::string Node::get_name() {
    return name;
}

std::string Node::get_path() {
    std::stack<std::string> pathStack;
    Node* current_node=this;
    // 从给定节点向上遍历父节点，直到根节点
    while (current_node != nullptr) {
        pathStack.push(current_node->name);
        current_node = current_node->parent;
    }

    // 构造路径字符串
    std::string path = "";
    while (!pathStack.empty()) {
        path += pathStack.top();
        pathStack.pop();
        if (!pathStack.empty()) {
            path += "/";
        }
    }
    return path;
}

void Node::print_child_as_tree(const std::string& prefix, bool isLast ) {
    // Print the current node's name with proper prefix
    std::cout << prefix;

    // Print the node connector
    std::cout << (isLast ? "└── " : "├── ");

    // Print the node name
    std::cout << name << std::endl;

    // Recursively print each child with the updated prefix
    for (size_t i = 0; i < children.size(); ++i) {
        children[i]->print_child_as_tree(prefix + (isLast ? "    " : "│   "), i == children.size() - 1);
    }
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
    if(parent){
        parent->children_cache[p_name]=this;
        parent->children_cache.erase(name);
    }
    name=p_name;
}

Node::Node() {
    ready();
}

