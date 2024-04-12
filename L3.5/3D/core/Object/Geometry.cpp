#include "Geometry.h"
Transform3D::Transform3D(){
    model_matrix=glm::mat4(1.f);
}
void Transform3D::translate(math::vec3 t){
    model_matrix*=glm::translate(glm::mat4(1.0),t);
}
void Transform3D::translate_local(math::vec3 t){
    model_matrix=glm::translate(model_matrix,t);
}
void Transform3D::scale(math::vec3 s){
    model_matrix*=glm::scale(glm::mat4(1.0),s);
}
void Transform3D::scale_local(math::vec3 s){
    model_matrix=glm::scale(model_matrix,s);
}
void Transform3D::rotate(math::vec3 axis,float degree){
    model_matrix*=glm::rotate(glm::mat4(1.0),degree*0.01745329251994f,axis);
}
void Transform3D::rotate_local(math::vec3 axis,float degree){
    model_matrix=glm::rotate(model_matrix,degree*0.01745329251994f,axis);
}
math::vec3 Transform3D::to_vector(math::vec3 vec) {
    return model_matrix*glm::vec4(vec,1.f);
}
float* Transform3D::get_matrix_ptr() {
    return glm::value_ptr(model_matrix);
}
Cube::Cube() {}

float* Cube::matrix_ptr() {
    return transform.get_matrix_ptr();
}
