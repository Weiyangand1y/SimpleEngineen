#pragma once
#include <string>
enum class KeyMode{RELEASE,PRESS,REPEAT};
enum class EventType{KEY,MOUSE,WINDOW};
struct KeyInfo{int key; int scancode; int action; int mods;};
struct FSCInfo{int width;int height;};
union EventInfo{
    KeyInfo key_info;
    FSCInfo fsc_info;
};
struct Event{
    std::string message;
    EventType event_type;        
    EventInfo info;
};