#include "SceneNode.h"
#include "Scene.h"
#include "L1/Debug/Log.h"
void SceneNode::create_from_scene(Scene* p_scene) {
    scene=p_scene;
    debug("SceneNode::create_from_scene\n");
}
