#include "L3/Object/SceneTreeCore/Node2D.h"
#include "L3/Object/SceneTreeCore/Camera.h"
class FollowCamera : public Node2D{
private:
    Camera* camera;
public:
    FollowCamera(){
    }
    void process(float delta)override{
        camera->set_center_position(m_position);
    }
    void set_camera(Camera* p_camera){
        camera=p_camera;
    }

};
