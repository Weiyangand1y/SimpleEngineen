#pragma once
#include "SceneNode.h"
#include "Camera.h"
#include "L1/Lib/Math/math.h"

class Viewport: public Node{
    Camera* camera;
public:
    //void ready() override;
    void set_camera(Camera* p_camera);
    mat4& get_transform_mat4();
};