#pragma once
#include <string>
#include <unordered_map>
#include <map>
#include "L2/Lib/imgui/MyImGui.h"
#include "ImageDB.h"
#include "rect_math.h"
class ImagePlatter{
private:
    struct Transform{
        ImVec2 position={50,50};
        ImVec2 size={100,100};
        float rotation=0.f;
    };
    struct UnitData{
        int id;
        std::string key;
        std::string sub_key;
        int texture_id;
        Transform transform;
        float left=0.f,right=1.f,top=1.f,bottom=0.f;//uv
    };
    struct State{
        UnitData* current_unit=nullptr;
        ImVec2 start_pos;
        ImVec2 object_start_pos;
        bool is_dragging=false;
        bool some_clicked=false;
    };
    std::unordered_map<int,UnitData> list;//<id, unit_data>
    std::map<int,int> list2;              //<z-index, id> need sort before
    ImageDB* image_db=nullptr;    
    State state;
public:
    void init(ImageDB* p_image_db){
        image_db=p_image_db;       
        load_from_db();
    }
    ImagePlatter(){
        list2[1]=0;
        list2[2]=1;
    }
    void load_from_db(){

        image_db->main_texture_table.select_one([](ImageDB::MainTexture& r){return true;},
        [&](ImageDB::MainTexture& r){
            list[0]={0,r.key,"",r.texture_id,{{350,150},{150,150/r.aspect_ratio},90}};
        }
        );
        image_db->sub_texture_table.select_one([](ImageDB::SubTexture& r){return true;},
        [&](ImageDB::SubTexture& r){
             float inv_ratio=(r.top-r.bottom)/((r.right-r.left)*r.aspect_ratio);
            list[1]={1,r.key,"",r.texture_id,{{150,150},{50,50*inv_ratio},45},
            r.left,r.right,r.top,r.bottom};
        }
        );

    }

    void render(){
        ImGui::Begin("Platter");
        ImGui::BeginChild("canvas",{500,500},ImGuiChildFlags_Border,ImGuiWindowFlags_NoMove);
        //std::sort(list2.begin(),list2.end());
        auto* draw_list=ImGui::GetWindowDrawList();        
        ImVec2 start_pos=ImGui::GetWindowPos();
        start_pos.y+=50;
        start_pos.x+=30;
        bool some_clicked=false;
        for(auto it=list2.rbegin();it!=list2.rend();++it){
            auto& unit=list[it->second];
            ImGui::Text("%s",unit.key.c_str());
            ImGui::SetNextItemAllowOverlap();
            ImVec2 target_pos={
                start_pos.x+unit.transform.position.x,
                start_pos.y+unit.transform.position.y
            };

            ImGui::ImageRotated((void*)(intptr_t)unit.texture_id,
                target_pos,
                unit.transform.size,
                unit.transform.rotation,
                {unit.left,unit.right,unit.top,unit.bottom}
            );
            if(ImGui::IsMouseClicked(ImGuiMouseButton_Left)&&ImGui::IsWindowHovered()){   
                auto mouse_pos=ImGui::GetMousePos();            
                if(is_point_inside_rectangle(
                    mouse_pos,target_pos,
                    unit.transform.size.x,unit.transform.size.y,
                    unit.transform.rotation)){   
                //
                    state.current_unit=&unit;
                    state.object_start_pos=unit.transform.position;
                    state.start_pos=mouse_pos;
                    state.is_dragging=true;
                    debug("{}\n",unit.key);
                    some_clicked=true;
                }
                
            }
            
        }//end for
        if(!some_clicked&&ImGui::IsMouseClicked(ImGuiMouseButton_Left))state.current_unit=nullptr;
        if(state.current_unit){
            auto mouse_pos=ImGui::GetMousePos();
            if(ImGui::IsMouseReleased(ImGuiMouseButton_Left))state.is_dragging=false;
            if(state.is_dragging){
                state.current_unit->transform.position=state.object_start_pos+mouse_pos-state.start_pos;
            }
            auto& t=state.current_unit->transform;
            ImVec2 target_pos=t.position+start_pos;
            float rr=glm::radians(t.rotation);
            ImVec2 f1={cosf(rr),sinf(rr)};
            ImVec2 f2={-sinf(rr),cosf(rr)};
            ImVec2 r1=t.size*ImVec2{0.5f,0.5f},r2=t.size*ImVec2{-0.5f,0.5f};
            ImVec2 r3=t.size*ImVec2{-0.5f,-0.5f},r4=t.size*ImVec2{0.5f,-0.5f};
            draw_list->AddQuad(
                target_pos+ImVec2{ dot(f1,r1),  dot(f2,r1) },
                target_pos+ImVec2{ dot(f1,r2),  dot(f2,r2) },
                target_pos+ImVec2{ dot(f1,r3),  dot(f2,r3) },
                target_pos+ImVec2{ dot(f1,r4),  dot(f2,r4) },
                IM_COL32(0,0,0,255),2.f
            );
        }
        draw_list->AddLine(start_pos,{start_pos.x+350,start_pos.y+150},0x998866ff,3.f);
        ImGui::EndChild();
        ImGui::End();
    }
};

