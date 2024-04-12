#include "DrawableNode.h"
#include "Scene.h"
#include "L1/Debug/Log.h"
void DrawableNode::enter_scene(Scene* scene) {
    SceneNode::enter_scene(scene);
    drawer=scene->app->get_drawer();
    Logger::log(0,"DrawableNode::enter_scene");
}


void DrawableNode::after_process(float delta) {
    if(visible)draw();    
}

void DrawableNode::draw() {
    assert(viewport);
}

