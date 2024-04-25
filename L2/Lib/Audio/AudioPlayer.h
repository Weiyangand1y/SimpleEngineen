#pragma once
#include <irrKlang.h>
#pragma comment(lib, "irrKlang.lib")
class AudioPlayer{
public:
    AudioPlayer(){
        irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();
        //engine->play2D("C:/Users/21wyc/Music/Audio/COLORALPHA 50 Menu Interface SFX/COLORALPHA 50 Menu Interface SFX/WAV/MI_SFX 01.wav", true);
    }
    
};