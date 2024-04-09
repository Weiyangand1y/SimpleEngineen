#include "Camera3D.h"
#include <unordered_map>
class CameraController{
private:
    Camera3D* m_camera;
public:
    CameraController();
    void set_camera(Camera3D* p_camera);
    void on_key_down(int key);
    void on_key_release(int key);
    void on_drag(float x,float y);
    void on_scroll(float scroll_y);
    void update();
private:
    std::unordered_map<Camera3D::Direction, bool> key_state;
};



