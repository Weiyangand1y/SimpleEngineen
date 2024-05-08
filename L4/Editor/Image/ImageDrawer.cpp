#include "ImageDrawer.h"
#include "L2/Lib/imgui/MyImGui.h"
void draw_image(const std::string& sub_id, const Rect& rect, ImageDB* image_db) {
    auto* draw_list=ImGui::GetWindowDrawList();
    auto* sub_image=image_db->sub_texture_table.select_by_key(sub_id);
    if(!sub_image)return;
    ImVec2 rect_min={rect.x-rect.w/2.f,rect.y-rect.h/2.f};
    ImVec2 rect_max={rect.x+rect.w/2.f,rect.y+rect.h/2.f};
    ImVec2 uv_min={sub_image->left,sub_image->top};
    ImVec2 uv_max={sub_image->right,sub_image->bottom};
    int id=sub_image->texture_id;
    draw_list->AddImage((void*)(intptr_t)id,rect_min,rect_max,uv_min,uv_max);
}

void ImageDrawer::init(ImageDB* image_db) {
    ImageDrawer::image_db=image_db;
}

void ImageDrawer::draw_image(const std::string& sub_id, const Rect& rect) {
    auto* draw_list=ImGui::GetWindowDrawList();
    auto* sub_image=image_db->sub_texture_table.select_by_key(sub_id);
    if(!sub_image)return;
    ImVec2 rect_min={rect.x-rect.w/2.f,rect.y-rect.h/2.f};
    ImVec2 rect_max={rect.x+rect.w/2.f,rect.y+rect.h/2.f};
    ImVec2 uv_min={sub_image->left,sub_image->top};
    ImVec2 uv_max={sub_image->right,sub_image->bottom};
    int id=sub_image->texture_id;
    draw_list->AddImage((void*)(intptr_t)id,rect_min,rect_max,uv_min,uv_max);
}
