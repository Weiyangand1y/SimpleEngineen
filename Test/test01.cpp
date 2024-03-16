#include <iostream>
#ifdef DEBUG
#include "spdlog/spdlog.h"
#include "termcolor.hpp"
#endif
#include "L1/App/Application.h"
#include "L1/Lib/Math/math.h"
#include "L2/Lib/imgui/MyImGui.h"
#include "L1/Object/ScriptObject.h"


class TestApplication:public Application{
public:
    void _init() override{
        std::cout<<"==============="<<std::endl;
        MyImGui::static_init(get_window()->get_window());
        ScriptObject so;

              
    }
    void _run() override{
        renderer.start_framebuffer("f1");  //--------------------
        renderer.clear_color();
        mat4 m(1.0f);
        m=rotate(m,radians(time*20.f), glm::vec3(0.0f, 0.0f, 1.0f));
        m=scale(m,vec3(0.3f, 0.3f, 1.f));
        m=translate(m,vec3(0.5f * sinf(time), 0.7f, 0.0));

        drawer.draw_texture(std::string("Claudette_Huy"), value_ptr(m));

        renderer.end_framebuffer();  //-------------------------

        drawer.draw_texture(renderer.get_framebuffer_color_texture_id("f1"),
                            Render::ShaderType::SCREEN);

        // renderer.start_framebuffer("f2");
        // drawer.draw_texture(renderer.get_framebuffer_color_texture_id("f1"),
        //                     Render::ShaderType::SCREEN);
        // renderer.end_framebuffer();

        MyImGui::static_begin();
        ImGui::Begin("Test");
        ImGui::Image((void*)renderer.get_framebuffer_color_texture_id("f1"),
                         ImVec2{300.f,300.f}, ImVec2{0,1}, ImVec2{1,0});
        ImGui::End();
        MyImGui::static_end();
    }
};

int main(){
    system("cls");
    #ifdef DEBUG
    spdlog::info("Hello, {}!", "World");
    std::cout << termcolor::red << "This text is red  " << termcolor::reset;
    std::cout << termcolor::green << "This text is green" << termcolor::reset << std::endl;
    #endif
    TestApplication app;
    app.init();
    app.run();
}