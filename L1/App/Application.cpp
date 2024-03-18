#include "Application.h"
#include "Config.h"
#include <iostream>

Application::Application(){
    auto [w,h]=Config::getInstance().get_windows_size();
    window.create(w,h,Config::getInstance().get("title").c_str());
    renderer.init();
    drawer.set_render(renderer);
}

void Application::init() {
    _init();
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
