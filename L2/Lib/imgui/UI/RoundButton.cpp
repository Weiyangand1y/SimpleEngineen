#include "RoundButton.h"
ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs)
{
    return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y);
}

ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs)
{
    return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y);
}
bool RoundedButton(const char* label, const ImVec2& size, float corner_radius, float border_thickness)
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
        s.x = label_size.x + style.FramePadding.x * 4.0f;
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
    draw_list->AddRect(bb.Min, bb.Max, IM_COL32(0, 0, 0, 255), corner_radius, ImDrawFlags_RoundCornersAll, border_thickness);

    ImGui::RenderTextClipped(bb.Min + style.FramePadding, bb.Max - style.FramePadding, label, nullptr, &label_size, style.ButtonTextAlign, &bb);

    return pressed;
}
