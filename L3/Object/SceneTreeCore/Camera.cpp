#include "Camera.h"

void Camera::update_mat() {
    float _left   =  center_position.x-left;
    float _right  =  center_position.x+right;
    float _bottom =  center_position.y-bottom;
    float _top    =  center_position.y+top;
    transform_mat4=ortho(_left,_right,_bottom,_top);
}

mat4& Camera::get_transform_mat4() {
    return transform_mat4;
}

Camera::Camera() {
    
    center_position=vec2(0.0f);
    top=bottom=80.f;
    right=left=120.f;
    update_mat();
}

Camera::Camera(vec2 p_center_position, vec2 p_half_wh)
                    :center_position(p_center_position) {
    top=bottom=p_half_wh.y;
    right=left=p_half_wh.x;
    update_mat();
}

void Camera::set_center_position(vec2 p_center_position) {
    center_position=p_center_position;
    update_mat();
}

void Camera::set_half_wh(vec2 p_half_wh) {
    top=bottom=p_half_wh.y;
    right=left=p_half_wh.x;
    update_mat();
}
