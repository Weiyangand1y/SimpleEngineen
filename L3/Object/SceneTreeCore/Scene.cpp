#include "Scene.h"
#include "L1/Debug/Log.h"

Scene::Scene(Application* p_app) {
    app=p_app;
    default_viewport=new Viewport();
    default_camera=new Camera();
    default_viewport->set_camera(default_camera);
    root_node=new SceneNode();
    root_node->set_viewport(default_viewport);
    let_node_know_scene(root_node);
}


void Scene::let_node_know_scene(SceneNode* scene_node) {
    debug("Scene::add_node\n");
    scene_node->create_from_scene(this);
}
