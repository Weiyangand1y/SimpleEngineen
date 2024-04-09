#include "Camera3D.h"
class CameraController{
private:
    Camera3D* m_camera;
public:
    CameraController();
    void on_key(int key);
    void on_drag(float x,float y);
    void on_scroll(float scroll_y);
};



