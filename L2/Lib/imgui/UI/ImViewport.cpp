#include "ImViewport.h"
#include "L1/Debug/Log.h"
#include "RoundButton.h"
void ImViewport::drawGui() {
    float y_from_x=0.6667f;
    ImGui::Begin("运行界面",0,ImGuiWindowFlags_NoMove);
    ImVec2 size = ImGui::GetWindowSize();
    ImGui::Image((void*)texture_id,
                        ImVec2{size.x,size.x*y_from_x}, ImVec2{0,1}, ImVec2{1,0});

    if (ImGui::IsItemHovered()) {
        auto& io=ImGui::GetIO();
        //click
        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
            if (mouse_click_callback) {
                auto p = ImGui::GetItemRectMin();
                auto q = io.MouseClickedPos[0];
                float delta_x = q.x - p.x;
                float delta_y = q.y - p.y;
                debug("p(im_image): {}, {}\n", delta_x, delta_y);
                float r_x=delta_x * 2 / size.x - 1.f;
                float r_y=-delta_y * 2 / (size.x * y_from_x) + 1.f;
                mouse_click_callback(r_x,r_y);
                signal.emit("click",{r_x,r_y});
            }
        }
        //scroll
        if(io.MouseWheel!=0.f){
            debug("scroll {}\n", io.MouseWheel);
            signal.emit("scroll",{io.MouseWheel});
        }
        //drag
        ImVec2 delta_len = ImGui::GetMouseDragDelta();
        if (delta_len.x != 0.f) {
            debug("drag {} {}\n", delta_len.x, delta_len.y);
            signal.emit("drag",{delta_len.x, delta_len.y});
        }
    }
    ImGui::SetNextItemAllowOverlap();
    ImGui::SetCursorPos({50,50});
    RoundedButton("Click");
    ImGui::End();
}
