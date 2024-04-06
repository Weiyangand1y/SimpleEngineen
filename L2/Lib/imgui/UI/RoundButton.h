#pragma once
#include "imgui.h"
#include "imgui_internal.h"
ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs);

ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs);
bool RoundedButton(const char* label, const ImVec2& size = ImVec2(0, 0), float corner_radius = 10.0f, float border_thickness = 1.0f);
