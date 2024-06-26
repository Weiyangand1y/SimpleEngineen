#pragma once
#include "L1/Lib/Math/math.h"

class Camera3D {
protected:
    math::mat4 projection_matrix;
    math::mat4 view_matrix;
public:
    enum class Direction {IDLE,FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN};

    bool projection_dirty=true;
    bool view_dirty=true;
    bool pos_dirty=true;

    virtual math::mat4& get_projection_matrix();
    math::mat4& get_view_matrix();
    void set_position(math::vec3 pos);
    void move(math::vec3 delta_move);
    void move_ralative_camera(Direction direnction,float delta_move);
    void rotate_pitch_yaw(float yaw, float pitch, float delta_move);
    virtual void scale_view(float value);
    math::vec3 m_position{0.f,0.f,1.f};
private:
    float m_yaw = -90.0f;
    float m_pitch = 0.0f;
    
    
    math::vec3 m_up{0.f,1.f,0.f};
    math::vec3 m_right{1.f,0.f,0.f};

};
