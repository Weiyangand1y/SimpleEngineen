#include "Camera.h"
#include "L1/Debug/Log.h"
void Camera::update_mat() {
    float _left   =  center_position.x-left;
    float _right  =  center_position.x+right;
    float _bottom =  center_position.y-bottom;
    float _top    =  center_position.y+top;
    transform_mat4=glm::ortho(_left,_right,_bottom,_top);
}

math::mat4& Camera::get_transform_mat4() {
    //debug("*** camera pos: {} {}\n",center_position.x,center_position.y);
    return transform_mat4;
}

Camera::Camera() {   
    center_position=math::vec2(0.0f);
    float radio=1.5f;
    top=bottom=80.f;
    right=left=top*1.5f;
    update_mat();
}

Camera::Camera(math::vec2 p_center_position, math::vec2 p_half_wh)
                    :center_position(p_center_position) {
    top=bottom=p_half_wh.y;
    right=left=p_half_wh.x;
    update_mat();
}

void Camera::set_center_position(math::vec2 p_center_position) {
    center_position=p_center_position;
    //debug("### camera pos: {} {}\n",center_position.x,center_position.y);
    update_mat();
}

void Camera::set_half_wh(math::vec2 p_half_wh) {
    top=bottom=p_half_wh.y;
    right=left=p_half_wh.x;
    update_mat();
}
