#pragma once
#include "L1/Lib/Math/math.h"

class Camera3D {
protected:
    math::mat4 projection_matrix;
    math::mat4 view_matrix;
public:
    enum class Direction {IDLE,FORWARD, BACKWARD, LEFT, RIGHT};

    bool projection_dirty=true;
    bool view_dirty=true;
    bool pos_dirty=true;

    virtual math::mat4& get_projection_matrix();
    math::mat4& get_view_matrix();
    void set_position(vec3 pos);
    void move(vec3 delta_move);
    void move_ralative_camera(Direction direnction,float delta_move);
    void rotate_pitch_yaw(float yaw, float pitch, float delta_move);
    vec3 m_position{0.f,0.f,1.f};
private:
    float m_yaw = -90.0f;
    float m_pitch = 0.0f;
    
    
    vec3 m_up{0.f,1.f,0.f};
    vec3 m_right{1.f,0.f,0.f};

};
