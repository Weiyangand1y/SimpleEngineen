#pragma once
#include "L1/App/Config.h"
#include "L1/App/Application.h"
#include "Viewport.h"
#include "Camera.h"

#include "SceneNode.h"
#include "DrawableNode.h"
class SceneNode;
class Scene{
public:
    Application* app;
    Viewport* default_viewport;
    Camera* default_camera;
    SceneNode* root_node;
    Scene(Application* p_app);

    void let_node_know_scene(SceneNode* scene_node);
};