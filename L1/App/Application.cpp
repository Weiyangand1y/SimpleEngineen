#include "Application.h"
#include "Config.h"
#include <iostream>
#include "L1/Debug/Log.h"
#include "L1/Debug/TimeMeasure.h"
Application::Application(){
    auto [w,h]=Config::getInstance().get_windows_size();
    window.create(w,h,Config::getInstance().get("title").c_str());
    renderer.init();
    drawer.set_render(renderer);
    drawer.draw_texture(Config::getInstance().get("start_screen_image"));
    window.swap_buffers();
}

void Application::init() {
    MEASURE_TIME2(
        "init ===> ",
        _init()
        );
}

void Application::_init() {
    std::cout<<"00000000000"<<std::endl;
}

void Application::run() {
    while (!window.should_close()) {
        float old_time = time;
        time = window.get_time();
        delta_time = time - old_time;
        window.poll_events();
        renderer.clear_color();
        _run();
        if(show_frame_run_time){
            static int count=0;
            if(count++%100==0){
            auto frame_run_time = window.get_time()-time;
            debug("delta time: {:.3f}ms ___ frame_run_time: {:.3f}  __  rate: {:.2f}% \n",
                        delta_time*1000.f,frame_run_time*1000.f,frame_run_time*100.f/delta_time);}
        }
        window.swap_buffers();
    }
}

void Application::_run() {}

Window* Application::get_window() {
    return &window;
}

Drawer* Application::get_drawer() {
    return &drawer;
}

Render* Application::get_renderer() {
    return &renderer;
}
