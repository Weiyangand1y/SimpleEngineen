#include "EventManager.h"
#include <iostream>
void EventManager::on_framebuffer_size_change(int width, int height) {
    event.event_type=EventType::WINDOW;
    event.info.fsc_info={width,height};
    send_event();
}

void EventManager::on_key(int key, int scancode, int action, int mods) {
    event.event_type=EventType::KEY;
    event.info.key_info={key,scancode,action,mods};
    send_event();
}



void EventManager::send_event() {}
