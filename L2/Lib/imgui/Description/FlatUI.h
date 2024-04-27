#pragma once
#include "FlatDescription.h"
#include "imgui_internal.h"
struct DrawData{
    const ImRect& bb;
    const char* label;
    const ImVec2& label_size;
};
void draw(FlatDescription::StateDecription& d, DrawData& draw_data){
    // Draw Box
    const ImU32 col = d.color.background.to_imgui_color();
    ImGui::RenderFrame(
        draw_data.bb.Min, draw_data.bb.Max, 
        col, true, d.border.r
        );
    // Draw Border
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    draw_list->AddRect(
        draw_data.bb.Min, draw_data.bb.Max, 
        d.border.color.to_imgui_color(), 
        d.border.r, 
        ImDrawFlags_RoundCornersAll, 
        d.border.thickness
        );
    ImGui::RenderTextClipped(
        draw_data.bb.Min + d.frame_padding, 
        draw_data.bb.Max - d.frame_padding, 
        draw_data.label, nullptr, 
        &draw_data.label_size, 
        ImVec2(0,0), 
        &draw_data.bb
        );
}
bool FlatButton(const char* label, FlatDescription& d){
    //获取当前环境
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = ImGui::CalcTextSize(label, nullptr, true);
    ImVec2 pos = window->DC.CursorPos;
    ImVec2 s=d.normal.size;
    //如果不设定尺寸，根据文本调整大小
    if (d.normal.size.x == 0)
        s.x = label_size.x + d.normal.frame_padding.x * 4.0f;
    if(s.x<40.f)s.x=40.f;
    if (d.normal.size.y == 0)
        s.y = label_size.y + d.normal.frame_padding.y * 2.0f;
    //注册矩形，用以自动布局，事件响应
    const ImRect bb(pos, pos + s);
    ImGui::ItemSize(bb, d.normal.frame_padding.y);
    if (!ImGui::ItemAdd(bb, id))
        return false;
    //获取事件
    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held);

    DrawData draw_data={bb,label,label_size};
    //根据状态切换分支
    if(held || hovered)ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
    if(held)draw(d.hold,draw_data);
    else if(hovered)draw(d.hover,draw_data);   
    else draw(d.normal,draw_data);

    return pressed;
}
