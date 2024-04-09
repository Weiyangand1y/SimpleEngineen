#include "OrthographicCamera.h"

mat4& OrthographicCamera::get_projection_matrix() {
    projection_matrix=ortho(m_left,m_right,m_bottom,m_top);
    projection_dirty=false;
    return projection_matrix;
}
