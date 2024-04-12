#include "L3.5/3D/core/Camera/PerspectiveCamera.h"
#include "L3.5/3D/core/Drawer3D.h"
#include "L3.5/3D/core/Camera/CameraController.h"
#include "L3.5/3D/core/Object/Geometry.h"
#include "L1/Debug/Log.h"
#include "L1/App/Application.h"
#include "L1/App/Config.h"
#include "L2/Lib/imgui/MyImGui.h"
class TDApp : public Application{
PerspectiveCamera camera;
CameraController camera_controller;
Drawer3D drawer3d;
std::vector<Cube> cube_list;
public:
    void _init(){
        auto [x,y]=Config::getInstance().get_windows_size();
        camera.m_aspect=float(x)/y;
        MyImGui::static_init(window.get_window());
        glEnable(GL_DEPTH_TEST);
        drawer3d.set_renderer(renderer);
        camera.set_position({2.f,2.f,15.f});
        camera_controller.set_camera(&camera);
        window.m_key_callback=[&](int key, int scancode, int action, int mods){
            if(action==1)camera_controller.on_key_down(key);
            else if(action==0)camera_controller.on_key_release(key);
        };
        cube_list.resize(10);
        math::vec3 cubePositions[] = {
            math::vec3( 0.0f,  0.0f,  0.0f),
            math::vec3( 2.0f,  5.0f, -15.0f),
            math::vec3(-1.5f, -2.2f, -2.5f),
            math::vec3(-3.8f, -2.0f, -12.3f),
            math::vec3( 2.4f, -0.4f, -3.5f),
            math::vec3(-1.7f,  3.0f, -7.5f),
            math::vec3( 1.3f, -2.0f, -2.5f),
            math::vec3( 1.5f,  2.0f, -2.5f),
            math::vec3( 1.5f,  0.2f, -1.5f),
            math::vec3(-1.3f,  1.0f, -1.5f)
        };
        for (int i = 0; i < cube_list.size(); i++){
            float angle = 20.0f * i;
            cube_list[i].t3d.translate_local(cubePositions[i]);
            cube_list[i].t3d.rotate_local(math::vec3(1.0f, 0.3f, 0.5f),angle);
        }
        
    }
    void _run(){
        //Logger::log(2,"fps: {}",1/delta_time);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
        camera_controller.update();
        if(camera.pos_dirty){
            debug("...p22\n");
            drawer3d.chnage_view_pos(camera.m_position.x,camera.m_position.y,camera.m_position.z);
        }
        if(camera.view_dirty){
            debug("...v\n");
            drawer3d.change_view_matrix(value_ptr(camera.get_view_matrix()));
        }
        if(camera.projection_dirty){
            debug("...p\n");
            drawer3d.change_projection_matrix(value_ptr(camera.get_projection_matrix()));
        }
        
        drawer3d.draw_ruler();
        Cube light_cube;
        light_cube.t3d.translate_local({-3,0,-3});
        light_cube.t3d.scale_local({.25f,.25f,.25f});

        vec4 lpos=light_cube.t3d.model_matrix*vec4(vec3(0.f),1.f);

        drawer3d.change_light_pos(lpos.x,lpos.y,lpos.z);
        drawer3d.draw_cube(light_cube.matrix_ptr());
        drawer3d.change_light_color(1.f+0.5f*sinf(time),1.f+0.5f*cos(time),0.f);
        
        for (unsigned int i = 0; i < 10; i++){
            cube_list[i].t3d.rotate_local(math::vec3(.0f, 0.f, 0.5f),glm::radians(delta_time*15.f));
            drawer3d.draw_cube(cube_list[i].matrix_ptr());
        }
        

        Cube materia_cube;
        materia_cube.t3d.translate_local({3,-3,3});
        drawer3d.draw_light_cube(materia_cube.matrix_ptr());

        MyImGui::static_begin();
        auto [dx,dy]=ImGui::GetMouseDragDelta(0);
        if(dx!=0.f || dy!=0.f){
            debug("dx: {}, dy:{}\n",dx,dy);
            camera_controller.on_drag(dx,dy);
        }
        MyImGui::static_end();
    }
};
int main(){
    system("cls");
    TDApp app;
    app.init();
    app.run();
}