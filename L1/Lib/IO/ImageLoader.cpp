#include "imageLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

unsigned char* ImageLoader::loadImage(const char* filename, int* width, int* height, int* channels) {
    stbi_set_flip_vertically_on_load(true);
    return stbi_load(filename, width, height, channels, 0);
}

void ImageLoader::free_data(unsigned char* data) {
    stbi_image_free(data);
}
