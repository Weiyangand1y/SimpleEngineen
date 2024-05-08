#include "MyDrag.h"

void MyGui::drag4f(const char* labels[4],int color[4],float* v[4],float speed,float min,float max) {
    ImGui::PushStyleColor(ImGuiCol_FrameBg,color[0]);
    ImGui::DragFloat(labels[0],v[0],speed,min,max);
    ImGui::PopStyleColor();
}
