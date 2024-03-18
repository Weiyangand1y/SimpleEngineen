#include "Viewport.h"

void Viewport::set_camera(Camera* p_camera) {
    camera=p_camera;
}

mat4& Viewport::get_transform_mat4() {
    assert(camera);
    return camera->get_transform_mat4();
}
