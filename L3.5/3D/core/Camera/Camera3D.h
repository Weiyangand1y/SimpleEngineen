#pragma once
#include "L1/Lib/Math/math.h"

class Camera3D {
protected:
    mat4 projection_matrix;
    mat4 view_matrix;
public:
    bool projection_dirty=true;
    bool view_dirty=true;
    virtual mat4& get_projection_matrix();
    mat4& get_view_matrix();
    void set_position(vec3 pos);
private:
    
    
    vec3 m_position{0.f,0.f,1.f};
    vec3 m_up{0.f,1.f,0.f};
    vec3 m_right{1.f,0.f,0.f};

};
