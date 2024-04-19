#include "ImagePlatter.h"
#include "rect_math.h"
#include <algorithm>

void ImagePlatter::set_z_index(int id,int z_index){
    for (auto& e : list2) {
        if (e.id == id) {
            e.z_index = z_index;
        }
    }
}
void ImagePlatter::set_drop_area(){
    if(ImGui::BeginDragDropTarget()){
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("key")){
            debug("{}   ----{}------",(const char*)payload->Data,payload->DataSize);
            strncpy(state.input_text,(const char*)payload->Data,payload->DataSize);
            debug("{}\n",state.input_text);
        }
        ImGui::EndDragDropTarget();
    }
}

void ImagePlatter::drop_to_here(){
    auto mouse_pos=ImGui::GetMousePos();
    auto center_pos=mouse_pos-state.start_pos;
    if(ImGui::BeginDragDropTarget()){
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("key")){
            add_unit(
                std::string((const char*)payload->Data,payload->DataSize),
                ImageType::MainImage,
                {center_pos}
                );
        }else if(const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("subkey")){
            add_unit(
                std::string((const char*)payload->Data),
                ImageType::SubImage,
                {center_pos}
                );
        }
        ImGui::EndDragDropTarget();
    }
}

void ImagePlatter::draw_image(UnitData& unit,const ImVec2& target_pos){
    ImGui::ImageRotated((void*)(intptr_t)unit.texture_id,
            target_pos,
            unit.transform.size,
            unit.transform.rotation,
            {unit.left,unit.right,unit.top,unit.bottom}
        );
}

void ImagePlatter::calculate_rect(ImVec2 vertex[4],UnitData& unit){
    auto& t=unit.transform;
    ImVec2 target_pos=state.start_pos+t.position;
    float rr=glm::radians(t.rotation);
    ImVec2 f1={cosf(rr),sinf(rr)}; ImVec2 f2={-sinf(rr),cosf(rr)};
    float d=10.f;
    ImVec2 r1=t.size*ImVec2{0.5f,  0.5f}+ImVec2{d,d},   r2=t.size*ImVec2{-0.5f,0.5f}+ImVec2{-d,d};
    ImVec2 r3=t.size*ImVec2{-0.5f,-0.5f}+ImVec2{-d,-d}, r4=t.size*ImVec2{0.5f,-0.5f}+ImVec2{d,-d};
    vertex[0]=target_pos+ImVec2{ dot(f1,r1),  dot(f2,r1) };
    vertex[1]=target_pos+ImVec2{ dot(f1,r2),  dot(f2,r2) };
    vertex[2]=target_pos+ImVec2{ dot(f1,r3),  dot(f2,r3) };
    vertex[3]=target_pos+ImVec2{ dot(f1,r4),  dot(f2,r4) };
}

void ImagePlatter::draw_border(UnitData& unit){
    auto* draw_list=ImGui::GetWindowDrawList();     
    ImVec2  p[4];//4个顶点 (1,1) (-1,1) (-1,-1) (1,-1)
    calculate_rect(p,*state.current_unit);
    draw_list->AddQuad(p[0],p[1],p[2],p[3],IM_COL32(0,0,0,255),2.f);
    ImVec2 small_size=ImVec2(5.f,5.f);
    for(auto& small_p:p){
        draw_list->AddRectFilled(small_p-small_size,small_p+small_size,0xffffffff);
        draw_list->AddRect(small_p-small_size,small_p+small_size,IM_COL32_BLACK,0.f,0,2.f);
    }
}

bool ImagePlatter::is_inside_unit_rect(const ImVec2& mouse_pos,const ImVec2& target_pos,UnitData& unit){
    return is_point_inside_rectangle(
                mouse_pos,target_pos,
                unit.transform.size.x,unit.transform.size.y,
                unit.transform.rotation);
}
void ImagePlatter::save_to_db(){
    for(auto& e:list){
        auto& element=e.second;
        std::string key=element.key+"_"+element.sub_key;
        auto& t=element.transform;
        image_db->image_scene_table.insert(key,[&](ImageDB::ImageScene& record){
            auto [px,py]=t.position;
            auto [sx,sy]=t.size;
            record={element.key,element.sub_key,
                    px,py,sx,sy,t.rotation,t.z_index};
    });
    }
    image_db->save_scene();    
}
    void ImagePlatter::add_unit(const std::string& key, ImageType type,const Transform& transform){
    auto [center_pos,p_size,rotation,z_index]=transform;
    if(type==ImageType::MainImage){
        image_db->main_texture_table.select_by_key(
            key,
            [&](ImageDB::MainTexture& r){
                if(r.key==""){
                    Logger::log(8,"Database_MainImage don't have [{}]",key); 
                    return;
                    }
                int id=id_pool.allocateID();
                ImVec2 size=p_size.x<0?ImVec2{150,150/r.aspect_ratio}:p_size;
                list[id]={id,r.key,"",r.texture_id,{center_pos,size,rotation,z_index}};
                list2.push_back({z_index,id});
            }
    );//lambda end
    }else if(type==ImageType::SubImage){
        image_db->sub_texture_table.select_by_key(
            key,
            [&](ImageDB::SubTexture& r){
                if(r.key==""){Logger::log(8,"Database_SubImage don't have [{}]",key); return;}
                int id=id_pool.allocateID();
                float inv_ratio=r.get_sub_inv_ratio();
                ImVec2 size=p_size.x<0?ImVec2{150,150*inv_ratio}:p_size;
                list[id]={id,r.key,r.sub_key,r.texture_id,{center_pos,size,rotation,z_index},
                r.left,r.right,r.top,r.bottom};
                list2.push_back({z_index,id});
            }
    );//lambda end
    }
}
void ImagePlatter::load_scene_from_db(){
    image_db->load_scene_from_file();
    image_db->image_scene_table.select_all([&](ImageDB::ImageScene& r){
        int id=id_pool.allocateID();
        ImageType type=r.sub_key==""?ImageType::MainImage:ImageType::SubImage;
        std::string key=r.sub_key==""?r.key:r.sub_key;
        add_unit(key,type,{{r.px,r.py},{r.sx,r.sy},r.r,r.z});
    });
}

void ImagePlatter::init(ImageDB* p_image_db){
    image_db=p_image_db;       
    load_from_db();
}
ImagePlatter::ImagePlatter(){
    id_pool.init(30);
}
void ImagePlatter::load_from_db(){
    // add_unit("Cream_Puff",ImageType::MainImage);
    // add_unit("Basic Charakter Actions2",ImageType::SubImage);
    load_scene_from_db();
}

void ImagePlatter::render(){
    ImGui::Begin("Platter");
    ImGui::BeginChild("canvas",{500,500},ImGuiChildFlags_Border,ImGuiWindowFlags_NoMove);
    auto* draw_list=ImGui::GetWindowDrawList();        
    ImVec2 start_pos=ImGui::GetWindowPos();
    start_pos.y+=50;
    start_pos.x+=30;
    state.start_pos=start_pos;
    bool some_clicked=false;
    std::stable_sort(list2.begin(),list2.end(),[](const ZindexPair&a, const ZindexPair& b){return a.z_index<b.z_index;});
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
                state.start_click_pos=mouse_pos;
                state.is_dragging=true;
                debug("{}\n",unit.key);
                some_clicked=true;                   
            }               
        }
        
    }//end for
    if(!some_clicked&&ImGui::IsMouseClicked(ImGuiMouseButton_Left)
            &&is_point_inside_rectangle(ImGui::GetMousePos(),start_pos,{500,500},false))
        state.current_unit=nullptr;
    if(state.current_unit){
        auto mouse_pos=ImGui::GetMousePos();
        if(ImGui::IsMouseReleased(ImGuiMouseButton_Left))state.is_dragging=false;
        if(state.is_dragging){
            state.current_unit->transform.position=state.object_start_pos+mouse_pos-state.start_click_pos;
        }
        draw_border(*state.current_unit);
        if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl)) {
            ImGui::BeginTooltip();
            auto& t = state.current_unit->transform;
            ImGui::Text("%s_%s", state.current_unit->key.c_str(), state.current_unit->sub_key.c_str());
            ImGui::Text("id:       %d", state.current_unit->id);
            ImGui::Text("pos:      %.1f %.1f", t.position.x, t.position.x);
            ImGui::Text("size:     %.1f %.1f", t.size.x, t.size.x);
            ImGui::Text("rotation: %.1f", t.rotation);
            ImGui::Text("z-index : %d", t.z_index);
            ImGui::EndTooltip();
        }
    }
    draw_list->AddLine(start_pos,{start_pos.x+350,start_pos.y+150},0x998866ff,3.f);
    ImGui::EndChild();
    drop_to_here();
    ImGui::Text("Information");
    if(state.current_unit){
        ImGui::DragFloat("rotation",&state.current_unit->transform.rotation,1.f,-180.f,180.f);
        ImGui::DragFloat2("size",&state.current_unit->transform.size.x,1.f,0.f,600.f);
        if(ImGui::InputInt("z-index",&state.current_unit->transform.z_index,1)){
            set_z_index(state.current_unit->id,state.current_unit->transform.z_index);
        }
    }
    ImGui::Text("Input Scene key");
    if(ImGui::InputText("scene key",state.input_text,64,ImGuiInputTextFlags_EnterReturnsTrue)){     
    }
    set_drop_area();
    if(ImGui::Button("Save")){
        save_to_db();
    }
    ImGui::End();
}