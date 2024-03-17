#pragma once
#include <string>
#include "event.h"
class EventManager{
public:   
    Event event;
    void on_framebuffer_size_change(int width,int height);
    void on_key(int key, int scancode, int action, int mods);
    virtual void send_event();
};