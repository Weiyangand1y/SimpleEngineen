#pragma once
#include "L1/Render/Renderer.h"
#include "Window.h"
#include "L1/Render/Drawer.h"

class Application{
protected:
    Window window;
    Render renderer;
    Drawer drawer;
    float time=0.f;
    float delta_time;
public:
    Application();
    void init();
    void run();
    virtual void _run();
};