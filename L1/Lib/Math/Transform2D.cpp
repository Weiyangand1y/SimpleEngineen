#include "Transform2D.h"
Transform2D::Transform2D(){
    model_matrix=glm::mat4(1.f);
}
void Transform2D::translate(math::vec2 t){
    model_matrix*=glm::translate(glm::mat4(1.0),glm::vec3(t,0.f));
}
void Transform2D::translate_local(math::vec2 t){
    model_matrix=glm::translate(model_matrix,glm::vec3(t,0.f));
}
void Transform2D::scale(math::vec2 t){
    model_matrix*=glm::scale(glm::mat4(1.0),glm::vec3(t,1.f));
}
void Transform2D::scale_local(math::vec2 t){
    model_matrix=glm::scale(model_matrix,glm::vec3(t,1.f));
}
void Transform2D::rotate_r(float r){  
    model_matrix*=glm::rotate(glm::mat4(1.0),r,glm::vec3(0.f,0.f,1.f));
}
void Transform2D::rotate_local_r(float r){
    model_matrix=glm::rotate(model_matrix,r,glm::vec3(0.f,0.f,1.f)); 
}
math::vec2 Transform2D::to_vector(math::vec2 vec){
    return model_matrix*glm::vec4(vec,0.f,1.f);
}
float* Transform2D::get_matrix_ptr(){
    return glm::value_ptr(model_matrix);
}