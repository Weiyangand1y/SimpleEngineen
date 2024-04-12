#include "Camera3D.h"
class OrthographicCamera:public Camera3D{
private:
    
public:
    math::mat4& get_projection_matrix()override;
    float m_left=10.f,m_right=10.f,m_top=10.f,m_bottom=10.f;
    float m_near=0.f,m_far=20.f;
};

