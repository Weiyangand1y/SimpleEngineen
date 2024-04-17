#pragma once
#include "L2/Lib/imgui/MyImGui.h"
#include "L1/Render/Renderer.h"
#include "ImageDB.h"
//load subtexture
class ImageCut{
    enum class Area{
        no,left,right,top,bottom
    //
    };
    struct ImageCutData{
        char key[64]={0};
        char input_text[64]={0};
        int texture_id=-1;
        float left=0.4f,right=0.6f,top=0.6f,bottom=0.4f;
        float aspect_ratio=1.f;
        char subkey[64]="...subkey";
    };
    struct State{
        bool is_dragging=false;
        ImVec2 start_pos;
        Area who;
    };
    ImageCutData data;
    State state;
    Area get_click(ImVec2 rect_min,ImVec2 rect_max,ImVec2 rect_size,ImVec2 start_pos){
        float threshold=0.05f;
        state.start_pos=start_pos;
        if(abs((start_pos.x-rect_min.x)/rect_size.x-data.left)<threshold)return Area::left;
        else if(abs((start_pos.x-rect_min.x)/rect_size.x-data.right)<threshold)return Area::right;
        else if(abs(1-(start_pos.y-rect_min.y)/rect_size.y-data.top)<threshold)return Area::top;
        else if(abs(1-(start_pos.y-rect_min.y)/rect_size.y-data.bottom)<threshold)return Area::bottom;
        else return Area::no;
    }
    void move(Area area,ImVec2 delta_move,ImVec2 rect_size,ImVec2 rect_min){
        switch (area){
        case Area::left:
            data.left=(state.start_pos.x+delta_move.x-rect_min.x)/rect_size.x;
            break;
        case Area::right:
            data.right=(state.start_pos.x+delta_move.x-rect_min.x)/rect_size.x;
            break;
        case Area::top:
            data.top=1-(state.start_pos.y+delta_move.y-rect_min.y)/rect_size.y;
            break;
        case Area::bottom:
            data.bottom=1-(state.start_pos.y+delta_move.y-rect_min.y)/rect_size.y;
            break;
        default:
            break;
        }
    }
public:
    ImageDB* image_db=nullptr;
    void init(ImageDB* p_image_db){
        image_db=p_image_db;       
    }
    void render(){
    
    ImGui::Begin("Image Cut");

    //load texture
        std::vector<ImageDB::MainTexture> list;
        image_db->main_texture_table.select_where([](ImageDB::MainTexture& record){
            return record.texture_id!=-1;
        },&list);
        ImGui::Text("Image Key");
        ImGui::InputTextWithHint("##key","Input image key",data.input_text,sizeof(data.input_text));
        ImGui::Text("Select your Image");
        if(ImGui::BeginListBox("##list")){
            for(auto& r : list){
                ImGui::Image(
                (void*)(intptr_t)r.texture_id,
                {30,30},{0,1},{1,0});
                ImGui::SameLine();
                bool is_selected=false;
                ImGui::Selectable(r.key.c_str(),&is_selected);
                if(is_selected){
                    debug(">>id: {}\n",r.key);
                    data.texture_id=r.texture_id;
                    data.aspect_ratio=r.aspect_ratio;
                    strncpy(data.key,r.key.c_str(),64);
                    strncpy(data.subkey,r.key.c_str(),64);
                }  
            }
        ImGui::EndListBox();}
        if(data.texture_id!=-1){
            ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
            ImGui::SeparatorText(data.key);
            ImGui::PopFont();
            ImGui::BeginChild("child",{0,0},0,ImGuiWindowFlags_NoMove);
            
            ImGui::SetCursorPosX(15);
            ImGui::Image(
                (void*)(intptr_t)data.texture_id,
                {300,300/data.aspect_ratio},{0,1},{1,0});
            
            auto rect_min=ImGui::GetItemRectMin();
            auto rect_max=ImGui::GetItemRectMax();
            auto rect_size=ImGui::GetItemRectSize();
            auto* draw_list=ImGui::GetWindowDrawList();
            
            auto top_y=rect_min.y+(rect_max.y-rect_min.y)*(1-data.top);
            auto bottom_y=rect_min.y+(rect_max.y-rect_min.y)*(1-data.bottom);
            auto left_x=rect_min.x+(rect_max.x-rect_min.x)*data.left;
            auto right_x=rect_min.x+(rect_max.x-rect_min.x)*data.right;

            draw_list->AddLine({rect_min.x-10,top_y},{rect_max.x+10,top_y},IM_COL32(255,0,32,255),3);
            draw_list->AddLine({rect_min.x-10,bottom_y},{rect_max.x+10,bottom_y},IM_COL32(68,175,240,255),3);
            draw_list->AddLine({left_x,rect_min.y-10},{left_x,rect_max.y+10},IM_COL32(255,0,32,255),3);
            draw_list->AddLine({right_x,rect_min.y-10},{right_x,rect_max.y+10},IM_COL32(68,175,240,255),3);            
            //ImageRotated((void*)(intptr_t)data.texture_id,{rect_min.x+100,rect_min.y+100},{300,300},15.f);
            if(ImGui::IsItemHovered()){
                auto pos=ImGui::GetMousePos();
                auto result=get_click(rect_min,rect_max,rect_size,pos);
                if(result!=Area::no)ImGui::SetMouseCursor(ImGuiMouseCursor_Hand); 
                if(ImGui::IsItemClicked()){ 
                    if(result!=Area::no){
                        state.start_pos=pos;
                        state.who=result;                                             
                    }else{ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);  }
                    state.is_dragging=true;
                }
                if(ImGui::IsMouseReleased(ImGuiMouseButton_Left))state.is_dragging=false;
                if(state.is_dragging){
                    ImVec2 delta_move={
                        ImGui::GetMousePos().x-state.start_pos.x,
                        ImGui::GetMousePos().y-state.start_pos.y
                        };
                    move(state.who,delta_move,rect_size,rect_min);
                    }
            }
            ImGui::EndChild();
            ImGui::Text("Image Key");
            ImGui::InputTextWithHint("##key","Input image key",data.subkey,sizeof(data.subkey));
            ImGui::SetCursorPosX(100);
            if(ImGui::Button("Save",{150,60})){
                image_db->insert_sub_texture(std::string(data.subkey),std::string(data.key),data.texture_id,
                data.left,data.right,data.top,data.bottom,data.aspect_ratio);
            }
            ImGui::Text("==>");
            float inv_ratio=(data.top-data.bottom)/((data.right-data.left)*data.aspect_ratio);
            ImGui::SetCursorPosX(15);
            ImGui::Image(
                (void*)(intptr_t)data.texture_id,
                {300,300*inv_ratio},{data.left,data.top},{data.right,data.bottom});
            //drag
            //who to click => get_who_clicked(min,max,lrbt) => l,r,b,t,lt,lb,rt,rb
        }
        //sub
        ImGui::Text("SubImage List");
        std::vector<ImageDB::SubTexture> list2;
        image_db->sub_texture_table.select_where([](ImageDB::SubTexture& record){
            return record.texture_id!=-1;
        },&list2);
        if(ImGui::BeginListBox("##list2")){
            for(auto& r : list2){
                float inv_ratio=(r.top-r.bottom)/((r.right-r.left)*r.aspect_ratio);
                ImGui::Image(
                (void*)(intptr_t)r.texture_id,
                {30,30*inv_ratio},{r.left,r.top},{r.right,r.bottom});  
                ImGui::SameLine();
                ImGui::Text("%s",r.sub_key.c_str());       
                if(ImGui::IsItemHovered()){
                    ImGui::SetItemTooltip("from %s",r.key.c_str());
                    ImGui::BeginTooltip();
                    ImGui::Image(
                (void*)(intptr_t)r.texture_id,
                {300,300*inv_ratio},{r.left,r.top},{r.right,r.bottom});  
                    ImGui::EndTooltip(); 
                    }   
            }
        ImGui::EndListBox();}
        
    //save
    ImGui::End();
    }
};