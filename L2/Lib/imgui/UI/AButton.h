#include "../MyImGui.h"
#include "imgui_internal.h"
bool AButton(const char* label, int texure_id, const ImVec2& size = ImVec2(0, 0), float corner_radius = 5.0f, float border_thickness = 1.0f)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = ImGui::CalcTextSize(label, nullptr, true);

    ImVec2 pos = window->DC.CursorPos;
    ImVec2 s=size;
    if (size.x == 0)
        s.x = label_size.x + style.FramePadding.x * 4.0f+label_size.y;
    if(s.x<40.f)s.x=40.f;
    if (size.y == 0)
        s.y = label_size.y + style.FramePadding.y * 2.0f;

    const ImRect bb(pos, pos + s);
    ImGui::ItemSize(bb, style.FramePadding.y);
    if (!ImGui::ItemAdd(bb, id))
        return false;

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held);

    // Render
    const ImU32 col = ImGui::GetColorU32((hovered && held) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
    ImGui::RenderFrame(bb.Min, bb.Max, col, true, corner_radius);

    // Draw border
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    draw_list->AddRect(bb.Min, bb.Max, IM_COL32(0, 0, 0, 255), 
    corner_radius, ImDrawFlags_RoundCornersAll, border_thickness);
    if(held){        
        draw_list->AddImage(
                (ImTextureID)(intptr_t)texure_id,
                {bb.Min.x+(s.x-s.y)/2.f,bb.Min.y},
                {bb.Min.x+(s.x+s.y)/2.f,bb.Max.y},
                {0,1},{1,0}
            );
        ImGui::RenderTextClipped(
                bb.Min+style.FramePadding,
                bb.Max - style.FramePadding,
                label, nullptr, &label_size, style.ButtonTextAlign, &bb
            );
    }
    else if(hovered){
        ImGui::RenderTextClipped(
                {bb.Min.x + style.FramePadding.x+s.y,pos.y},
                bb.Max - style.FramePadding,
                label, nullptr, &label_size, style.ButtonTextAlign, &bb
            );
        draw_list->AddImage(
                (ImTextureID)(intptr_t)texure_id,
                bb.Min + style.FramePadding, 
                {bb.Min.x + style.FramePadding.x+s.y,bb.Max.y},
                {0,1},{1,0}
            );
    }else{
    ImGui::RenderTextClipped(
        bb.Min + style.FramePadding, 
        bb.Max - style.FramePadding-ImVec2{s.y,0}, 
        label, nullptr, &label_size, style.ButtonTextAlign, &bb
        );
    draw_list->AddImage((ImTextureID)(intptr_t)texure_id,
                {bb.Max.x - style.FramePadding.x-s.y,pos.y},
                bb.Max - style.FramePadding,
                {0,1},{1,0}
                );
    }
    return pressed;
}
