#include "L3.5/3D/core/Camera/PerspectiveCamera.h"
#include "L3.5/3D/core/Drawer3D.h"
#include "L3.5/3D/core/Camera/CameraController.h"
#include "L3.5/3D/core/Object/Geometry.h"
#include "L3.5/3D/core/Light/Light.h"

#include "L1/Debug/Log.h"
#include "L1/App/Application.h"
#include "L1/App/Config.h"
#include "L2/Lib/imgui/MyImGui.h"
#include "L3.5/3D/core/model/Model.h"

#include <thread>
#include <chrono>

class TDApp : public Application{
PerspectiveCamera camera;
CameraController camera_controller;
Drawer3D drawer3d;
std::vector<Cube> cube_list;
LightData light_data;
math::vec3 a_cube_position={0,0,0};
Model model;
int id=0;
public:
    void _run(){
        //std::this_thread::sleep_for(std::chrono::milliseconds(50));
        //Logger::log(2,"fps: {}",1/delta_time);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera_controller.update();//action -> change
        if(camera.pos_dirty){
            debug("...p22\n");
            drawer3d.chnage_view_pos(camera.m_position.x,camera.m_position.y,camera.m_position.z);
        }
        if(camera.view_dirty){
            debug("...v\n");
            drawer3d.change_view_matrix(glm::value_ptr(camera.get_view_matrix()));
        }
        if(camera.projection_dirty){
            debug("...p\n");
            drawer3d.change_projection_matrix(value_ptr(camera.get_projection_matrix()));
        }
        
        drawer3d.draw_ruler();
        Cube light_cube;
        light_cube.transform.translate_local({-3,0,-3});
        light_cube.transform.scale_local({.25f,.25f,.25f});

        math::vec3 lpos=light_cube.transform.to_vector({0,0,0});

        //drawer3d.change_light_pos(lpos.x,lpos.y,lpos.z);
        drawer3d.draw_cube(light_cube.matrix_ptr());
        drawer3d.change_light_color(1.f+0.5f*sinf(time),1.f+0.5f*cos(time),0.f);
        
        for (unsigned int i = 0; i < 10; i++){
            cube_list[i].transform.rotate_local(math::vec3(.0f, 0.f, 0.5f),delta_time*15.f);
            drawer3d.draw_cube(cube_list[i].matrix_ptr());
        }
        

        Cube materia_cube;
        materia_cube.transform.translate_local({5,-5,5});
        materia_cube.transform.scale_local({5,5,5});        
        drawer3d.draw_light_cube(materia_cube.matrix_ptr());

        materia_cube.transform.model_matrix=glm::mat4(1.f);
        materia_cube.transform.translate_local({0,-5,0});
        materia_cube.transform.scale_local({50,1,50});        
        drawer3d.draw_light_cube(materia_cube.matrix_ptr());

        MyImGui::static_begin();
        if(ImGui::GetIO().WantCaptureMouse==false){
            auto [dx,dy]=ImGui::GetMouseDragDelta(0);
            if(dx!=0.f || dy!=0.f){
                debug("dx: {}, dy:{}\n",dx,dy);
                camera_controller.on_drag(dx,dy);
            }
        }
        
        ImGui::Begin("Control SpotLight");
        ImGui::SeparatorText("SpotLight");
        ImGui::Text("OuterCutOff");
        if(ImGui::DragFloat("##SpotLight.outerCutOff",&light_data.spot_light.outerCutOff,3.0f,0.f,89.f)){
            if(light_data.spot_light.outerCutOff-light_data.spot_light.cutOff<0.01F){
                light_data.spot_light.outerCutOff=light_data.spot_light.cutOff+0.01f;
            }else{
                drawer3d.change_light("spotLight.outerCutOff",glm::cos(glm::radians(light_data.spot_light.outerCutOff)));
            }
            
        }
        ImGui::Text("CutOff");
        if(ImGui::DragFloat("##SpotLight.cutOff",&light_data.spot_light.cutOff,3.0f,0.f,89.f)){
            if(light_data.spot_light.outerCutOff-light_data.spot_light.cutOff<0.01F){
                light_data.spot_light.cutOff=light_data.spot_light.outerCutOff-0.01f;
            }else{
                drawer3d.change_light("spotLight.cutOff",glm::cos(glm::radians(light_data.spot_light.cutOff)));
            }            
        }
        ImGui::Text("Direction");
        if(ImGui::DragFloat3("##SpotLight.direction",&light_data.spot_light.direction.x,0.02f,-1.f,1.0f)){
            drawer3d.change_light("spotLight.direction",light_data.spot_light.direction);
        }
        ImGui::Text("Position");
        if(ImGui::DragFloat3("##SpotLight.position",&light_data.spot_light.position.x,1.f,-20.f,20.0f)){
            drawer3d.change_light("spotLight.position",light_data.spot_light.position);
        }      
        ImGui::End();
        ImGui::Begin("Direct Light");
        ImGui::Text("Diffuse");
        if(ImGui::DragFloat3("##dirLight.diffuse",&light_data.dir_light.diffuse.x,0.1f,0.f,1.f)){
            drawer3d.change_light("dirLight.diffuse",light_data.dir_light.diffuse);
        }
        ImGui::End();
        ImGui::Begin("Cube");
        if(ImGui::DragFloat3("#cube",&a_cube_position.x)){
            
        }
        Transform3D t;
        t.translate_local(a_cube_position);
        drawer3d.draw_ruler(t.get_matrix_ptr(),1.f,0.f);
        ImGui::InputInt("id",&id);
        if(id>5)ImGui::Image((ImTextureID)id,{100,100});
        ImGui::End();
        Shader& s=renderer.get_shader("model");
        s.use();
        t.translate({0,5,0});
        s.setMat4("model",t.get_matrix_ptr());
        model.Draw(s);

        MyImGui::static_end();
    }

    void _init(){        
        auto [x,y]=Config::getInstance().get_windows_size();
        model.start(Config::getInstance().get("model_path"));
        camera.m_aspect=float(x)/y;
        MyImGui::static_init(window.get_window());
        ImGui::GetIO().IniFilename="test09.ini";
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
            math::vec3( 1.3f, -5.0f, -2.5f),
            math::vec3( 1.5f,  2.0f, -2.5f),
            math::vec3( 1.5f,  0.2f, -1.5f),
            math::vec3(-1.3f,  1.0f, -1.5f)
        };
        for (int i = 0; i < cube_list.size(); i++){
            float angle = 20.0f * i;
            cube_list[i].transform.translate_local(cubePositions[i]);
            cube_list[i].transform.rotate_local(math::vec3(1.0f, 0.3f, 0.5f),angle);
        }
        
    }

};
int main(){
    system("cls");
    TDApp app;
    app.init();
    app.run();
}