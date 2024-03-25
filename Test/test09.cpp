#include "L3.5/3D/core/Camera3D.h"
#include "L1/Debug/Log.h"
#include "L1/App/Application.h"
#include "L1/App/Config.h"
class TDApp : public Application{
Camera3D camera;
public:
    void _init(){
        //renderer.get_texture_db().load("p1","C:/Users/21wyc/Pictures/Screenshots/aPicture.png");
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
        camera.setPos({0.f,0.f,cosf(time)*20.f+30.f});
        renderer.use_vertex(Render::VertexType::TEX_CUBE);
        Shader& s=renderer.get_shader("simple_cube");
        s.use();
        renderer.use_texture("p1",0);
        renderer.use_texture("Pippi_Carter",1);
        s.setInt("texture1",0);
        s.setInt("texture2",1);
        mat4 view=camera.GetViewMatrix();
        auto [w,h]=Config::getInstance().get_windows_size();
        mat4 projection = 
                    glm::perspective(
                        glm::radians(camera.getZoom()), (float)w / (float)h, 0.1f, 100.0f);
        s.setMat4("view",value_ptr(view));
        s.setMat4("projection",value_ptr(projection));

        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            s.setMat4("model", value_ptr(model));

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