#pragma once

class ImageLoader{
public:
    unsigned char* loadImage(const char* filename, int* width, int* height, int* channels);
    void free_data(unsigned char*);
};


