#include "Camera3D.h"
#include "L1/Debug/Log.h"
math::mat4& Camera3D::get_projection_matrix() {
    return projection_matrix;
}

math::mat4& Camera3D::get_view_matrix() {
    vec3 front=cross(m_up,m_right);
    view_matrix=lookAt(m_position, m_position + front, m_up);
    view_dirty=false;
    pos_dirty=false;
    return view_matrix;
}


void Camera3D::set_position(vec3 pos) {
    m_position=pos;
    view_dirty=true;
}

void Camera3D::move(vec3 delta_move) {
    set_position(m_position+delta_move);
}

void Camera3D::move_ralative_camera(Direction direction, float delta_move) {
    vec3 front=cross(m_up,m_right);
    switch (direction){
    case Direction::FORWARD:
        m_position += front * delta_move;
        break;
    case Direction::BACKWARD:
        m_position -= front * delta_move;
        break;
    case Direction::LEFT:
        m_position -= m_right * delta_move;
        break;
    case Direction::RIGHT:
        m_position += m_right * delta_move;
        break;    
    }
    view_dirty=true;
    pos_dirty=true;
}

void Camera3D::rotate_pitch_yaw(float yaw, float pitch, float delta_move) {
    view_dirty=true;
    m_yaw+=yaw*delta_move;
    m_pitch+=pitch*delta_move;
    vec3 front;
    front.x = cos(radians(m_yaw)) * cos(radians(m_pitch));
    front.y = sin(radians(m_pitch));
    front.z = sin(radians(m_yaw)) * cos(radians(m_pitch));
    front = normalize(front);
    Logger::log(1,"[{},{},{}]",front.x,front.y,front.z);
    m_right = normalize(cross(front, vec3(0.f,1.f,0.f)));
    m_up = normalize(cross(m_right, front));
}

