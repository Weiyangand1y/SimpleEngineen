#include "PerspectiveCamera.h"

math::mat4& PerspectiveCamera::get_projection_matrix(){
    projection_matrix=perspective(radians(m_fov),m_aspect,m_near,m_far);
    projection_dirty=false;
    return projection_matrix;
}
