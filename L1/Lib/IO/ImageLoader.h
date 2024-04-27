#pragma once

class ImageLoader{
public:
    unsigned char* loadImage(const char* filename, 
                                int* width, int* height, int* channels,bool is_flip_y=true);
    static void free_data(unsigned char*);
};


