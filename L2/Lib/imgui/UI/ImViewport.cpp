#include "ImViewport.h"
#include "L1/Debug/Log.h"
void ImViewport::drawGui() {
    ImGui::Begin("运行界面",0,ImGuiWindowFlags_NoMove);
    ImVec2 size = ImGui::GetWindowSize();
    ImGui::Image((void*)texture_id,
                        ImVec2{size.x,size.x*0.6667f}, ImVec2{0,1}, ImVec2{1,0});
    if(ImGui::IsItemHovered()){
        if(ImGui::IsMouseClicked(ImGuiMouseButton_Left)){
        auto p=ImGui::GetItemRectMin();
        auto q=ImGui::GetIO().MouseClickedPos[0];
        float delta_x=q.x-p.x;
        float delta_y=q.y-p.y;
        debug("p: {}, {}\n",delta_x,delta_y);
        mouse_click_callback(delta_x*2/size.x-1.f,-delta_y*2/(size.x*0.6667f)+1.f);
    }
    ImVec2 delta_len=ImGui::GetMouseDragDelta();
    if(delta_len.x!=0.f){
        debug("drag {} {}\n",delta_len.x,delta_len.y);
    }

    }
    
    ImGui::End();
}
