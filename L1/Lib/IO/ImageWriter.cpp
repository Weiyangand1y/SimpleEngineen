#include "imageWriter.h"
#include <glad/glad.h>
#include <vector>
#include <iostream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

void write_image(const std::string& filename, const int width, const int height){
        // 创建缓冲区来存储像素数据
    std::vector<unsigned char> pixels(width * height * 4);

    // 读取attachment的像素数据
    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());

    // 反转像素数据的行顺序
    std::vector<unsigned char> flipped_pixels(width * height * 4);
    for (int y = 0; y < height; y++) {
        memcpy(&flipped_pixels[(height - y - 1) * width * 4], &pixels[y * width * 4], width * 4);
    }

    // 使用stb库将像素数据编码为png格式并保存到文件中
    if (!stbi_write_png(filename.c_str(), width, height, 4, flipped_pixels.data(), width * 4)) {
        std::cerr << "Error: Failed to save framebuffer to png file: " << filename << std::endl;
    }
}