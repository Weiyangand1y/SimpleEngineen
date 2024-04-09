#include "PerspectiveCamera.h"

mat4 PerspectiveCamera::get_projection_matrix(){
    return perspective(radians(m_fov),m_aspect,m_near,m_far);
}
