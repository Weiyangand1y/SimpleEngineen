#include "PerspectiveCamera.h"
#include "L1/Debug/Log.h"
math::mat4& PerspectiveCamera::get_projection_matrix(){
    projection_matrix=glm::perspective(glm::radians(m_fov),m_aspect,m_near,m_far);
    projection_dirty=false;
    return projection_matrix;
}

void PerspectiveCamera::scale_view(float value) {
    m_fov-=value;
    projection_dirty=true;
}
