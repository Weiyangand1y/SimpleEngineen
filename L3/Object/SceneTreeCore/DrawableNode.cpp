#include "DrawableNode.h"
#include "Scene.h"
#include "L1/Debug/Log.h"
void DrawableNode::create_from_scene(Scene* scene) {
    SceneNode::create_from_scene(scene);
    drawer=scene->app->get_drawer();
    debug("DrawableNode::create_from_scene\n");
}


void DrawableNode::after_process(float delta) {
    draw();
}

void DrawableNode::draw() {
    drawer->draw_triangle(0.f,0.f);
    drawer->draw_texture("Pippi_Carter",value_ptr(viewport->get_transform_mat4()) );
}

