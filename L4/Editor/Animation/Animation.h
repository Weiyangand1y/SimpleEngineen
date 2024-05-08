#pragma once
#include <vector>
class Animation{
    class Frame{

    };
    std::vector<Frame> frames;
    int index=0;
    bool is_playing=false;
    void play(){}
    void stop(){}
    void update(){}
};