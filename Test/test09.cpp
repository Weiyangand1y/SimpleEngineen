#include "L3.5/3D/core/Camera/PerspectiveCamera.h"
#include "L3.5/3D/core/Drawer3D.h"
#include "L1/Debug/Log.h"
#include "L1/App/Application.h"
#include "L1/App/Config.h"
class TDApp : public Application{
PerspectiveCamera camera;
Drawer3D drawer3d;
public:
    void _init(){
        drawer3d.set_renderer(renderer);
        camera.set_position({0.f,0.f,15.f});
    }
    void _run(){
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
        glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };
        if(camera.view_dirty){
            debug("...v\n");
            drawer3d.change_view_matrix(value_ptr(camera.get_view_matrix()));
        }
        if(camera.projection_dirty){
            debug("...p\n");
            drawer3d.change_projection_matrix(value_ptr(camera.get_projection_matrix()));
        }

        
        

        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            drawer3d.change_transform_matrix(value_ptr(model));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }
};
int main(){
    system("cls");
    TDApp app;
    app.init();
    app.run();
}