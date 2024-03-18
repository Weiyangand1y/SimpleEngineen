#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "L1/Render/Drawer.h"
#include "L2/Event/Event.h"
class Node {
public:
    void addChild(Node* node);
    void removeChild(Node* node);
    virtual void ready();
    virtual void process(float delta);
    void _process(float delta);

    virtual void after_process(float delta);
    void _after_process(float delta);

    Node(std::string p_name);
    Node();


protected:
    std::vector<Node*> children;
    Node* parent;
    std::string name="@node";
};