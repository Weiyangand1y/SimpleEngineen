#pragma once
#include "DrawableNode.h"
#include "Camera.h"
#include "L1/Lib/Math/math.h"
#include "L1/Lib/OpengL/Buffer/FrameBuffer.h"
class Viewport: public DrawableNode{
    Camera* camera;
    FrameBuffer fb;
public:
    Viewport();
    void        set_camera(Camera* p_camera);
    Camera*     get_camera();
    math::mat4& get_view_projection_matrix();

    void        add_child(SceneNode* node)override;
    void        _after_process(float delta)override;
};