#include "Camera3D.h"
class PerspectiveCamera: public Camera3D{
private:
    
public:
    mat4 get_projection_matrix()override;
    float m_fov=45.f;
    float m_aspect=1.f;
    float m_near=1.f,m_far=100.f;
};