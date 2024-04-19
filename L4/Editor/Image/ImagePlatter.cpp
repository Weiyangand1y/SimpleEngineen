#include "ImagePlatter.h"
#include "rect_math.h"
#include <algorithm>

void ImagePlatter::sort_unit_by_z_index() {
    std::stable_sort(list2.begin(),list2.end(),[](const ZindexPair&a, const ZindexPair& b){return a.z_index<b.z_index;});
}

void ImagePlatter::set_z_index(int id, int z_index) {
    for (auto& e : list2) {
        if (e.id == id) {
            e.z_index = z_index;
        }
    }
}

void ImagePlatter::drop_to_here(){
    auto mouse_pos=ImGui::GetMousePos();
    auto center_pos=mouse_pos-state.start_pos;
    if(ImGui::BeginDragDropTarget()){
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("key")){
            add_unit(
                std::string((const char*)payload->Data),
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

void ImagePlatter::handle_border(UnitData& unit){  
    calculate_rect(state.rect_vertex,*state.current_unit);    
    if(ImGui::IsMouseClicked(ImGuiMouseButton_Left))state.resize_state.some_clicked=false;
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
int ImagePlatter::add_unit(const std::string& key, ImageType type,const Transform& transform){
    auto [center_pos,p_size,rotation,z_index]=transform;
    int return_id=-1;
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
                return_id=id;
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
                return_id=id;
            }
    );//lambda end
    }
    return return_id;
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

void ImagePlatter::handle_control_point(const ImVec2& point) {
    float r=5.f;
    ImVec2 mouse_pos=ImGui::GetMousePos();
    auto delta=mouse_pos-point;
    if(dot(delta,delta)<r*r){
        ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
        if(ImGui::IsMouseClicked(ImGuiMouseButton_Left)){
            debug("resize\n");
            state.resize_state.some_clicked=true;
        }
    }
}

void ImagePlatter::draw_border() {
    auto* draw_list=ImGui::GetWindowDrawList();   
    draw_list->AddQuad(state.rect_vertex[0],state.rect_vertex[1],
                       state.rect_vertex[2],state.rect_vertex[3],IM_COL32(0,0,0,255),2.f);
    ImVec2 small_size=ImVec2(5.f,5.f);
    for(auto& small_p:state.rect_vertex){
        ImVec2 left_top=small_p-small_size;
        ImVec2 right_bottom=small_p+small_size;
        draw_list->AddRectFilled(left_top,right_bottom,0xffffffff);
        draw_list->AddRect(left_top,right_bottom,IM_COL32_BLACK,0.f,0,2.f);
        handle_control_point(small_p);
    }
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
    start_pos+={30,50};
    state.start_pos=start_pos;
    state.move_state.some_clicked=false;
    sort_unit_by_z_index();
    //先处理边框，防止点击边框时实际为点击了其他元素或清空unit
    if(state.current_unit){
        handle_border(*state.current_unit);
    }
    for(auto it=list2.begin();it!=list2.end();++it){
        auto& unit=list[it->id];
        ImVec2 target_pos=start_pos+unit.transform.position;
        draw_image(unit,target_pos);
        handle_canvas_clicked(target_pos, unit);
    }//end for
    draw_border();
    if(!state.move_state.some_clicked&&ImGui::IsMouseClicked(ImGuiMouseButton_Left)
            &&is_point_inside_rectangle(ImGui::GetMousePos(),start_pos,{500,500},false)
            &&!state.resize_state.some_clicked)
        state.current_unit=nullptr;
    if(state.current_unit){
        auto mouse_pos=ImGui::GetMousePos();
        if(ImGui::IsMouseReleased(ImGuiMouseButton_Left))state.move_state.is_dragging=false;
        if(state.move_state.is_dragging){
            state.current_unit->transform.position=
                 state.move_state.object_start_pos
                +mouse_pos
                -state.move_state.start_click_pos;
        }
        
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

    if(ImGui::Button("Save")){
        save_to_db();
    }

    if (ImGui::Button("Add")) {
        undo_list.push_back(std::make_shared<AddCommand>("Cream_Puff", ImageType::MainImage, ImVec2(350, 150), this));
        undo_list.back()->execute();
    }
    if(ImGui::Button("Delete")){
        if(state.current_unit){
            undo_list.push_back(std::make_shared<DeleteCommand>(state.current_unit->id, this));
            undo_list.back()->execute();
        }
    }
    if (ImGui::Button("undo")) {
        if (!undo_list.empty()) {
            undo_list.back()->undo();
            redo_list.push_back(std::move(undo_list.back()));
            undo_list.pop_back();
        }
    }
    if(ImGui::Button("redo")){
        if(!redo_list.empty()){
            redo_list.back()->execute();
            undo_list.push_back(std::move(redo_list.back()));
            redo_list.pop_back();
        }
    }
    ImGui::End();
}

void ImagePlatter::handle_canvas_clicked(ImVec2& target_pos,ImagePlatter::UnitData& unit) {
    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
        auto mouse_pos = ImGui::GetMousePos();
        if (!state.resize_state.some_clicked && is_inside_unit_rect(mouse_pos, target_pos, unit)) {
            state.current_unit = &unit;
            state.move_state.object_start_pos = unit.transform.position;
            state.move_state.start_click_pos = mouse_pos;
            state.move_state.is_dragging = true;
            debug("{}\n", unit.key);
            state.move_state.some_clicked = true;
        }
    }
}

ImagePlatter::AddCommand::AddCommand(std::string key,ImageType type,ImVec2 pos,ImagePlatter* env)
    :env(env),pos(pos),key(key),type(type){}

void ImagePlatter::AddCommand::execute() {
    int return_id=env->add_unit(key,type,{pos});
    if(return_id==-1)Logger::log(8,"AddCommand failed");
    id=return_id;
}

void ImagePlatter::AddCommand::undo() {
    debug("undo\n");
    env->list.erase(id);
    env->list2.erase(std::remove_if(env->list2.begin(),env->list2.end(),
                        [&](const auto& e){return e.id==id;})
                    );
    env->id_pool.releaseID(id);
}

ImagePlatter::DeleteCommand::DeleteCommand(int id, ImagePlatter* env) {
    this->id = id;
    this->env = env;
    data = env->list[id];   
}

void ImagePlatter::DeleteCommand::execute() {
    env->list.erase(id);
    env->list2.erase(std::remove_if(env->list2.begin(),env->list2.end(),
                        [&](const auto& e){return e.id==id;})
                    );
    env->id_pool.releaseID(id);
}

void ImagePlatter::DeleteCommand::undo() {
    env->add_unit(data.key, data.sub_key == "" ? ImageType::MainImage : ImageType::SubImage, data.transform);
}
