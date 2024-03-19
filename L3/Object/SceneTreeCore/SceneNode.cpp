#include "SceneNode.h"
#include "Scene.h"
#include "L1/Debug/Log.h"
#include "Viewport.h"
void SceneNode::create_from_scene(Scene* p_scene) {
    scene=p_scene;
    debug("SceneNode::create_from_scene\n");
}

void SceneNode::add_child(SceneNode* node) {
    addChild(node);
    assert(viewport);
    node->viewport=viewport;
}

void SceneNode::set_viewport(Viewport* p_viewport) {
    viewport=p_viewport;
}
