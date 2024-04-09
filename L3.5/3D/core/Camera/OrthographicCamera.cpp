#include "OrthographicCamera.h"

mat4 OrthographicCamera::get_projection_matrix() {
    return ortho(m_left,m_right,m_bottom,m_top);
}
