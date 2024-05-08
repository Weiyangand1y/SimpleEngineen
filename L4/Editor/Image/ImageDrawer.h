#pragma once
#include "ImageDB.h"
#include "L1/Lib/Math/Geometry.h"
void draw_image(const std::string& sub_id, const Rect& rect, ImageDB* image_db);
class ImageDrawer{
    ImageDB* image_db=nullptr;
public:
    ImageDrawer(){}
    void init(ImageDB* image_db);
    void draw_image(const std::string& sub_id, const Rect& rect);
};