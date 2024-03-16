#include "Application.h"
#include <iostream>

Application::Application()
    : window(800, 800, "My Window"), renderer(), drawer(renderer) {
    init();
}

void Application::init() {}

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
