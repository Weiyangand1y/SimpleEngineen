#include "CameraController.h"

CameraController::CameraController() {
    for(auto&& e:key_state){
        e.second=false;
    }
}

void CameraController::set_camera(Camera3D* p_camera) {
    m_camera=p_camera;
}

void CameraController::on_key_down(int key) {
    switch (key){
    case 'W':
        key_state[Camera3D::Direction::FORWARD]=true;
        break;
    case 'S':
        key_state[Camera3D::Direction::BACKWARD]=true;
        break;
    case 'A':
        key_state[Camera3D::Direction::LEFT]=true;
        break;
    case 'D':
        key_state[Camera3D::Direction::RIGHT]=true;
        break;
    case 'Q':
        key_state[Camera3D::Direction::UP]=true;
        break;
    case 'E':
        key_state[Camera3D::Direction::DOWN]=true;
        break;
    }
}

void CameraController::on_key_release(int key) {
    switch (key){
    case 'W':
        key_state[Camera3D::Direction::FORWARD]=false;
        break;
    case 'S':
        key_state[Camera3D::Direction::BACKWARD]=false;
        break;
    case 'A':
        key_state[Camera3D::Direction::LEFT]=false;
        break;
    case 'D':
        key_state[Camera3D::Direction::RIGHT]=false;
        break;
    case 'Q':
        key_state[Camera3D::Direction::UP]=false;
        break;
    case 'E':
        key_state[Camera3D::Direction::DOWN]=false;
        break;
    }
}

void CameraController::on_drag(float x, float y) {
    float speed=0.2f;
    float len=sqrtf(x*x+y*y);
    m_camera->rotate_pitch_yaw(-x/len,y/len,speed);
}

void CameraController::on_scroll(float scroll_y) {
    float speed=5.f;   
    m_camera->scale_view(scroll_y*speed);
}

void CameraController::update() {
    float speed=0.05f;
    for(auto&& e:key_state){
        if(e.second==true){
            m_camera->move_ralative_camera(e.first,speed);
        }
    }
}
