#include "Geometry.h"
Transform3D::Transform3D(){
    model_matrix=mat4(1.f);
}
void Transform3D::translate(math::vec3 t){
    model_matrix*=glm::translate(mat4(1.0),t);
}
void Transform3D::translate_local(math::vec3 t){
    model_matrix=glm::translate(model_matrix,t);
}
void Transform3D::scale(math::vec3 s){
    model_matrix*=glm::scale(mat4(1.0),s);
}
void Transform3D::scale_local(math::vec3 s){
    model_matrix=glm::scale(model_matrix,s);
}
void Transform3D::rotate(math::vec3 axis,float angle){
    model_matrix*=glm::rotate(mat4(1.0),angle,axis);
}
void Transform3D::rotate_local(math::vec3 axis,float angle){
    model_matrix=glm::rotate(model_matrix,angle,axis);
}
float* Transform3D::get_matrix_ptr() {
    return glm::value_ptr(model_matrix);
}
Cube::Cube() {}

float* Cube::matrix_ptr() {
    return t3d.get_matrix_ptr();
}
