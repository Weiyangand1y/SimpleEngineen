#pragma once
#include <string>
#include <unordered_map>
#include <algorithm>
#include "L2/Lib/imgui/MyImGui.h"
#include "L2/Object/IDPool.h"
#include "ImageDB.h"
#include "rect_math.h"
class ImagePlatter{
private:
    IDPool id_pool;
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
    struct ZindexPair{
        int z_index;
        int id;
    };
    struct State{
        UnitData* current_unit=nullptr;
        ImVec2 start_pos;
        ImVec2 object_start_pos;
        bool is_dragging=false;
        bool some_clicked=false;
        char input_text[64]={0};
    };
    std::unordered_map<int,UnitData> list;//<id, unit_data>
    std::vector<ZindexPair> list2;           //<z-index, id> need sort before
    ImageDB* image_db=nullptr;    
    State state;
    void set_drop_area(){
        if(ImGui::BeginDragDropTarget()){
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("key")){
                debug("{}   ----{}------",(const char*)payload->Data,payload->DataSize);
                strncpy(state.input_text,(const char*)payload->Data,payload->DataSize);
                debug("{}\n",state.input_text);
            }
            ImGui::EndDragDropTarget();
        }
    }
    void draw_image(UnitData& unit,const ImVec2& target_pos){
        ImGui::ImageRotated((void*)(intptr_t)unit.texture_id,
                target_pos,
                unit.transform.size,
                unit.transform.rotation,
                {unit.left,unit.right,unit.top,unit.bottom}
            );
    }
    void draw_border(UnitData& unit,const ImVec2& start_pos){
        auto* draw_list=ImGui::GetWindowDrawList();       
        auto& t=state.current_unit->transform;
        ImVec2 target_pos=start_pos+t.position;
        float rr=glm::radians(t.rotation);
        ImVec2 f1={cosf(rr),sinf(rr)};
        ImVec2 f2={-sinf(rr),cosf(rr)};
        float d=10.f;
        ImVec2 r1=t.size*ImVec2{0.5f,0.5f}+ImVec2{d,d},r2=t.size*ImVec2{-0.5f,0.5f}+ImVec2{-d,d};
        ImVec2 r3=t.size*ImVec2{-0.5f,-0.5f}+ImVec2{-d,-d},r4=t.size*ImVec2{0.5f,-0.5f}+ImVec2{d,-d};
        ImVec2  p[4]={target_pos+ImVec2{ dot(f1,r1),  dot(f2,r1) },
                target_pos+ImVec2{ dot(f1,r2),  dot(f2,r2) },
                target_pos+ImVec2{ dot(f1,r3),  dot(f2,r3) },
                target_pos+ImVec2{ dot(f1,r4),  dot(f2,r4) }};
        draw_list->AddQuad(p[0],p[1],p[2],p[3],IM_COL32(0,0,0,255),2.f);
        ImVec2 small_size=ImVec2(5.f,5.f);
        for(auto& small_p:p){
            draw_list->AddRectFilled(small_p-small_size,small_p+small_size,0xffffffff);
            draw_list->AddRect(small_p-small_size,small_p+small_size,IM_COL32_BLACK,0.f,0,2.f);
        }

    }
    bool is_inside_unit_rect(const ImVec2& mouse_pos,const ImVec2& target_pos,UnitData& unit){
        return is_point_inside_rectangle(
                    mouse_pos,target_pos,
                    unit.transform.size.x,unit.transform.size.y,
                    unit.transform.rotation);
    }
    
    void add_unit(const std::string& key, ImageType type){
        if(type==ImageType::MainImage){
            image_db->main_texture_table.select_by_key(key,
        [&](ImageDB::MainTexture& r){
            if(r.key==""){Logger::log(8,"Database_MainImage don't have [{}]",key); return;}
            int id=id_pool.allocateID();
            list[id]={id,r.key,"",r.texture_id,{{350,150},{150,150/r.aspect_ratio},10}};
            list2.push_back({0,id});
        }
        );
        }else if(type==ImageType::SubImage){
            image_db->sub_texture_table.select_by_key(key,
        [&](ImageDB::SubTexture& r){
            if(r.key==""){Logger::log(8,"Database_SubImage don't have [{}]",key); return;}
            int id=id_pool.allocateID();
            float inv_ratio=r.get_sub_inv_ratio();
            list[id]={id,r.key,"",r.texture_id,{{150,150},{50,50*inv_ratio},45},
            r.left,r.right,r.top,r.bottom};
            list2.push_back({0,id});
        }
        );
        }
    }
public:
    void init(ImageDB* p_image_db){
        image_db=p_image_db;       
        load_from_db();
    }
    ImagePlatter(){
        id_pool.init(30);
    }
    void load_from_db(){
        //add_unit("Cream_Puff2",ImageType::MainImage);
        add_unit("Cream_Puff",ImageType::MainImage);
        add_unit("Basic Charakter Actions2",ImageType::SubImage);
    }

    void render(){
        ImGui::Begin("Platter");
        ImGui::BeginChild("canvas",{500,500},ImGuiChildFlags_Border,ImGuiWindowFlags_NoMove);
        auto* draw_list=ImGui::GetWindowDrawList();        
        ImVec2 start_pos=ImGui::GetWindowPos();
        start_pos.y+=50;
        start_pos.x+=30;
        bool some_clicked=false;
        std::stable_sort(list2.begin(),list2.end(),[](const ZindexPair&a, const ZindexPair& b){return a.z_index>b.z_index;});
        for(auto it=list2.begin();it!=list2.end();++it){
            auto& unit=list[it->id];
            ImGui::Text("%s",unit.key.c_str());
            ImGui::SetNextItemAllowOverlap();
            ImVec2 target_pos=start_pos+unit.transform.position;
            draw_image(unit,target_pos);
            if(ImGui::IsMouseClicked(ImGuiMouseButton_Left)){   
                auto mouse_pos=ImGui::GetMousePos();            
                if(is_inside_unit_rect(mouse_pos,target_pos,unit)){   
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
            draw_border(*state.current_unit,start_pos);
        }
        draw_list->AddLine(start_pos,{start_pos.x+350,start_pos.y+150},0x998866ff,3.f);
        ImGui::EndChild();
        set_drop_area();
        ImGui::Text("Input image key to add");
        
        if(ImGui::InputText("image_key",state.input_text,64,ImGuiInputTextFlags_EnterReturnsTrue)){
            std::string content=std::string(state.input_text);
            if(content.substr(0,4)=="sub-"){
                add_unit(content.substr(4),ImageType::SubImage);
            }else{
                add_unit(content,ImageType::MainImage);
            }        
        }
        set_drop_area();
        ImGui::End();
    }
};

