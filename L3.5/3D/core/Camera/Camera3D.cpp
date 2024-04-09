#include "Camera3D.h"

// Camera3D::Camera3D(vec3 position, vec3 up, float yaw, float pitch)
//     : Front(vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(2.5f), MouseSensitivity(0.1f), Zoom(45.0f) {
//     Position = position;
//     WorldUp = up;
//     Yaw = yaw;
//     Pitch = pitch;
//     updateCameraVectors();
// }

// Camera3D::Camera3D(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
//     : Front(vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(2.5f), MouseSensitivity(0.1f), Zoom(45.0f) {
//     Position = vec3(posX, posY, posZ);
//     WorldUp = vec3(upX, upY, upZ);
//     Yaw = yaw;
//     Pitch = pitch;
//     updateCameraVectors();
// }

mat4 Camera3D::get_projection_matrix() {
    return mat4();
}

mat4 Camera3D::get_view_matrix() {
    vec3 front=cross(m_up,m_right);
    return lookAt(m_position, m_position + front, m_up);
}

// void Camera3D::process_keyboard(Camera_Movement direction, float deltaTime) {
//     float velocity = MovementSpeed * deltaTime;
//     if (direction == FORWARD)
//         Position += Front * velocity;
//     if (direction == BACKWARD)
//         Position -= Front * velocity;
//     if (direction == LEFT)
//         Position -= Right * velocity;
//     if (direction == RIGHT)
//         Position += Right * velocity;
// }

// void Camera3D::proces_mouse_movement(float xoffset, float yoffset, bool constrainPitch) {
//     xoffset *= MouseSensitivity;
//     yoffset *= MouseSensitivity;

//     Yaw += xoffset;
//     Pitch += yoffset;

//     if (constrainPitch) {
//         if (Pitch > 89.0f)
//             Pitch = 89.0f;
//         if (Pitch < -89.0f)
//             Pitch = -89.0f;
//     }

//     updateCameraVectors();
// }

// void Camera3D::process_mouse_scroll(float yoffset) {
//     Zoom -= static_cast<float>(yoffset);
//     if (Zoom < 1.0f)
//         Zoom = 1.0f;
//     if (Zoom > 45.0f)
//         Zoom = 45.0f;
// }

void Camera3D::set_position(vec3 pos) {
    m_position=pos;
}

// void Camera3D::updateCameraVectors() {
//     vec3 front;
//     front.x = cos(radians(Yaw)) * cos(radians(Pitch));
//     front.y = sin(radians(Pitch));
//     front.z = sin(radians(Yaw)) * cos(radians(Pitch));
//     Front = normalize(front);

//     Right = normalize(cross(Front, WorldUp));
//     Up = normalize(cross(Right, Front));
// }
