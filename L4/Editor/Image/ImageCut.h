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
    struct MainImageListState{
        bool is_show=true;
    };
    struct State{
        MainImageListState mil_state;
        bool is_dragging=false;
        ImVec2 start_pos;
        Area who;
    };
    ImageCutData data;
    State state;
    void draw_small_image(int texture_id,float size){
        ImGui::Image(
                (void*)(intptr_t)texture_id,
                {size,size},{0,1},{1,0});
    }
    void draw_image(int texture_id,ImVec2 size,const ImVec2& uv1={0,1},const ImVec2& uv2={1,0}){
        ImGui::Image((void*)(intptr_t)texture_id,size,uv1,uv2);
    }
    void make_image_tool_tip(int texture_id,float inv_ratio,float width,const ImVec2& uv1={0,1},const ImVec2& uv2={1,0}) {
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::Image((void*)(intptr_t)texture_id, {width, width * inv_ratio},uv1, uv2);
            ImGui::EndTooltip();
        }
    }
    void set_drag(const char* type,const std::string& data){
        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID)) {
            ImGui::Text(data.c_str());
            ImGui::SetDragDropPayload(type, data.c_str(), data.size());
            ImGui::EndDragDropSource();
        }
    }
    void draw_main_image_list(){
        ImGui::Text("Image Key");
        ImGui::InputTextWithHint("##key","Input image key",data.input_text,sizeof(data.input_text));
        ImGui::Text("Select your Image");ImGui::SameLine();
        ImGui::Checkbox("##main",&state.mil_state.is_show);
        if(!state.mil_state.is_show)return;
        if(ImGui::BeginListBox("##list")){
            image_db->main_texture_table.select_all([&](ImageDB::MainTexture& r){
                bool is_selected=false;               
                draw_small_image(r.texture_id,30);
                
                make_image_tool_tip(r.texture_id,1/r.aspect_ratio,200);
                set_drag("key",r.key);
                ImGui::SameLine();                
                ImGui::Selectable(r.key.c_str(),&is_selected);
                if(is_selected)load_main_image(r);  
                set_drag("key",r.key);
                                                 
            });
        ImGui::EndListBox();}
    }
    void draw_cut_area(){
        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
            ImGui::SeparatorText(data.key);
            ImGui::PopFont();
            ImGui::BeginChild("child",{400,400},0,ImGuiWindowFlags_NoMove|ImGuiWindowFlags_HorizontalScrollbar);
            
            ImGui::SetCursorPosX(15);
            draw_image(data.texture_id,{300,300/data.aspect_ratio});
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
                        state.is_dragging=true;
                        state.start_pos=pos;
                        state.who=result;                                             
                    }else{ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);  }
                    
                }
                if(ImGui::IsMouseReleased(ImGuiMouseButton_Left))state.is_dragging=false;
                if(state.is_dragging){
                    ImVec2 delta_move=ImGui::GetMousePos()-state.start_pos;
                    move(state.who,delta_move,rect_size,rect_min);
                    }
            }
            ImGui::EndChild();
            ImGui::Text("SubImage Key");
            ImGui::InputTextWithHint("##subkey","Input sub-image key",data.subkey,sizeof(data.subkey));
            ImGui::SetCursorPosX(100);
            if(ImGui::Button("Save",{150,60})){
                image_db->insert_sub_texture(std::string(data.subkey),std::string(data.key),data.texture_id,
                data.left,data.right,data.top,data.bottom,data.aspect_ratio);
                image_db->save_to_file();
            }
            ImGui::Text("==>");
            float inv_ratio=(data.top-data.bottom)/((data.right-data.left)*data.aspect_ratio);
            ImGui::SetCursorPosX(15);
            draw_image(data.texture_id,{300,300*inv_ratio},{data.left,data.top},{data.right,data.bottom});
            //drag
            //who to click => get_who_clicked(min,max,lrbt) => l,r,b,t,lt,lb,rt,rb
        
    }
    void draw_sub_image_list(){
        ImGui::Text("SubImage List");       
        if(ImGui::BeginListBox("##list2")){
            image_db->sub_texture_table.select_all([&](ImageDB::SubTexture& r){
            float inv_ratio=r.get_sub_inv_ratio();
            draw_image(r.texture_id,{30,30*inv_ratio},{r.left,r.top},{r.right,r.bottom});
            make_image_tool_tip(r.texture_id,inv_ratio,200,{r.left,r.top},{r.right,r.bottom});
            set_drag("subkey",r.sub_key);  
            ImGui::SameLine();
            bool is_selected=false;
            ImGui::Selectable(r.sub_key.c_str(),&is_selected);   
            set_drag("subkey",r.sub_key);          
            if(is_selected)load_sub_image(r.sub_key);

        });
        ImGui::EndListBox();}
    }
    void load_sub_image(const std::string& subkey){
        image_db->sub_texture_table.select_one([&](ImageDB::SubTexture& r){
            return r.sub_key==subkey;
        },[&](ImageDB::SubTexture& r){
            debug(">>id: {}\n",r.sub_key);
            data.texture_id=r.texture_id;
            data.aspect_ratio=r.aspect_ratio;
            data.left=r.left;data.right=r.right;data.top=r.top;data.bottom=r.bottom;
            strncpy(data.key,r.key.c_str(),64);
            strncpy(data.subkey,r.sub_key.c_str(),64);
        } );        
    }
    void load_main_image(ImageDB::MainTexture& r){
        debug(">>id: {}\n",r.key);
        data.texture_id=r.texture_id;
        data.aspect_ratio=r.aspect_ratio;
        strncpy(data.key,r.key.c_str(),64);
        strncpy(data.subkey,r.key.c_str(),64);
    }
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
    
        draw_main_image_list();
        if(data.texture_id!=-1)draw_cut_area();
        draw_sub_image_list();

    ImGui::End();
    }
};