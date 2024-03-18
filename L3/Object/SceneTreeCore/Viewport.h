#pragma once
#include "L1/Object/Node.h"
#include "Camera.h"
#include "L1/Lib/Math/math.h"

class Viewport: public Node{
    Camera* camera;
public:
    mat4& get_transform_mat4();
};