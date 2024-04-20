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

void ImagePlatter::calculate_and_update_unit_rect_pos(ImVec2 vertex[4],UnitData& unit){
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
    update_border();
    if(ImGui::IsMouseClicked(ImGuiMouseButton_Left))state.resize_state.some_clicked=false;
    int index=0;
    for(auto& small_p:state.rect_vertex){
        bool result = on_control_point_pre(small_p);
        if(result)break;
        index++;
    }
    if(state.resize_state.some_clicked){
        debug("vertex: {}\n",index)
        state.resize_state.is_dragging=true;
        state.resize_state.fixed_pos=state.rect_vertex[(index+2)%4];
        state.resize_state.move_pos=state.rect_vertex[index];
        state.resize_state.start_click_pos=ImGui::GetMousePos();
    }
}

bool ImagePlatter::is_inside_unit_rect(const ImVec2& mouse_pos, UnitData& unit){
    ImVec2 target_pos=state.start_pos+unit.transform.position;
    return is_point_inside_rectangle(
                mouse_pos,target_pos,
                unit.transform.size.x,unit.transform.size.y,
                unit.transform.rotation);
}
void ImagePlatter::save_to_db(){
    for(auto& e:list){
        auto& element=e.second;
        std::string key=element.key+"_"+element.sub_key+std::string("_")+std::to_string(element.id);
        auto& t=element.transform;
        image_db->image_scene_table2.insert(key,[&](ImageDB::ImageScene& record){
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

bool ImagePlatter::on_control_point_pre(const ImVec2& point) {
    float r=5.f;
    ImVec2 mouse_pos=ImGui::GetMousePos();
    auto delta=mouse_pos-point;
    if(dot(delta,delta)<r*r){
        state.resize_state.some_clicked=true;
        return true;      
    }
    return false;
}

void ImagePlatter::draw_border() {
    if(!state.current_unit)return;
    update_border();
    auto* draw_list=ImGui::GetWindowDrawList();   
    draw_list->AddQuad(state.rect_vertex[0],state.rect_vertex[1],
                       state.rect_vertex[2],state.rect_vertex[3],IM_COL32(0,0,0,255),2.f);
    ImVec2 small_size=ImVec2(5.f,5.f);
    for(auto& small_p:state.rect_vertex){
        ImVec2 left_top=small_p-small_size;
        ImVec2 right_bottom=small_p+small_size;
        draw_list->AddRectFilled(left_top,right_bottom,0xffffffff);
        draw_list->AddRect(left_top,right_bottom,IM_COL32_BLACK,0.f,0,2.f);
    }
}

void ImagePlatter::start_canvas() {
    auto* draw_list = ImGui::GetWindowDrawList();
    // 与窗口左上角的偏移
    ImVec2 offset={30,50};
    state.start_pos = ImGui::GetWindowPos()+offset;
    sort_unit_by_z_index();
}

void ImagePlatter::preccess_input_from_canvas() {
    if(ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        on_canvas_pressed();
    else if(ImGui::IsMouseReleased(ImGuiMouseButton_Left))
        on_canvas_released();
    else 
        on_canvas_dragging();
}

void ImagePlatter::on_canvas_pressed() {
    debug("pressed\n");
    auto mouse_pos = ImGui::GetMousePos();
    bool is_in_canvas=is_point_inside_rectangle(mouse_pos,state.start_pos,{500,500},false);
    // 1. 先处理边框，防止点击边框时实际为点击了其他元素或清空unit
    if (state.current_unit) {
        handle_border(*state.current_unit);
    }
    // 2. 对每个unit处理点击事件
    state.move_state.some_clicked = false;
    UnitData* tmp_unit_ptr = nullptr;
    for (auto it = list2.begin(); it != list2.end(); ++it) {
        auto& unit = list[it->id];
        bool is_on_click = on_unit_clicked_pre(unit);
        if(is_on_click)tmp_unit_ptr=&unit;
    }
    if(tmp_unit_ptr)on_unit_clicked(*tmp_unit_ptr);

    
    // 3. 如果没有点击到任何unit和边框，清空current_unit
    bool is_nothing_clicked = !state.move_state.some_clicked && !state.resize_state.some_clicked;
    if (is_nothing_clicked && is_in_canvas)
            state.current_unit = nullptr;
}

void ImagePlatter::on_canvas_released() {
    if(state.resize_state.is_dragging){
        state.resize_state.is_dragging=false;
    }
    if(state.move_state.is_dragging){
        state.move_state.is_dragging=false;
    }
}

void ImagePlatter::on_canvas_dragging() {
    auto mouse_pos = ImGui::GetMousePos();
    bool hover_on_border=false;
    for(auto& small_p:state.rect_vertex){
        bool result = on_control_point_pre(small_p);
        if(result){hover_on_border=true;break;}
    }
    if(hover_on_border)
        ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
    else ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
    if(state.current_unit){
        // 1. resize
        if (state.resize_state.is_dragging) {
            //
            do_resize();
        }
        // 2. move
        if (state.move_state.is_dragging) {
            ImVec2 delta_move=mouse_pos - state.move_state.start_click_pos;
            state.current_unit->transform.position =
                state.move_state.object_start_pos + delta_move;
            update_border();
        }
    }
}

void ImagePlatter::draw_canvas() {
    for (auto it = list2.begin(); it != list2.end(); ++it) {
        auto& unit = list[it->id];
        ImVec2 target_pos = state.start_pos + unit.transform.position;
        draw_image(unit, target_pos);
    }  // end for
    draw_border();
    if (state.current_unit) {        
        if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl)) {
            ImGui::BeginTooltip();
            auto& t = state.current_unit->transform;
            ImGui::Text("%s_%s", state.current_unit->key.c_str(),
                        state.current_unit->sub_key.c_str());
            ImGui::Text("id:       %d", state.current_unit->id);
            ImGui::Text("pos:      %.1f %.1f", t.position.x, t.position.x);
            ImGui::Text("size:     %.1f %.1f", t.size.x, t.size.x);
            ImGui::Text("rotation: %.1f", t.rotation);
            ImGui::Text("z-index : %d", t.z_index);
            ImGui::EndTooltip();
        }
    }
}

void ImagePlatter::init(ImageDB* p_image_db){
    image_db=p_image_db;       
    load_from_db();
}
ImagePlatter::ImagePlatter(){
    id_pool.init(60);
}
void ImagePlatter::load_from_db(){
    // add_unit("Cream_Puff",ImageType::MainImage);
    // add_unit("Basic Charakter Actions2",ImageType::SubImage);
    load_scene_from_db();
}

void ImagePlatter::render(){
    ImGui::Begin("Platter");
    update_canvas();
    update_control_area();
    ImGui::End();
}

void ImagePlatter::update_control_area() {
    ImGui::Text("Information");
    if (state.current_unit) {
        ImGui::DragFloat("rotation", &state.current_unit->transform.rotation,
                         1.f, -180.f, 180.f);
        ImGui::DragFloat2("size", &state.current_unit->transform.size.x, 1.f,
                          0.f, 600.f);
        if (ImGui::InputInt("z-index", &state.current_unit->transform.z_index,
                            1)) {
            set_z_index(state.current_unit->id,
                        state.current_unit->transform.z_index);
        }
    }
    ImGui::Text("Input Scene key");
    if (ImGui::InputText("scene key", state.input_text, 64,
                         ImGuiInputTextFlags_EnterReturnsTrue)) {
    }

    if (ImGui::Button("Save")) {
        save_to_db();
    }

    if (ImGui::Button("Add")) {
        undo_list.push_back(std::make_shared<ImagePlatterCommand::AddCommand>(
            "Cream_Puff", ImageType::MainImage, ImVec2(350, 150), this));
        undo_list.back()->execute();
    }
    if (ImGui::Button("Delete")) {
        if (state.current_unit) {
            undo_list.push_back(
                std::make_shared<ImagePlatterCommand::DeleteCommand>(state.current_unit->id, this));
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
    if (ImGui::Button("redo")) {
        if (!redo_list.empty()) {
            redo_list.back()->execute();
            undo_list.push_back(std::move(redo_list.back()));
            redo_list.pop_back();
        }
    }
}

void ImagePlatter::update_canvas() {
    ImVec2 canvas_size = {500, 500};
    const ImGuiChildFlags child_flags = ImGuiChildFlags_Border;
    const ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoMove;    
    ImGui::BeginChild("canvas", canvas_size, child_flags, window_flags);
        start_canvas();
        preccess_input_from_canvas();
        draw_canvas();
    ImGui::EndChild(); 
    drop_to_here();
}

bool ImagePlatter::on_unit_clicked_pre(ImagePlatterType::UnitData& unit) {
    auto mouse_pos = ImGui::GetMousePos();

    bool is_not_resize = !state.resize_state.some_clicked;
    bool is_inside_unit = is_inside_unit_rect(mouse_pos,  unit);
    bool is_inside_current_border = 
                        state.current_unit 
                        && state.current_unit!=&unit 
                        && is_inside_unit_rect(mouse_pos,  *state.current_unit);
    bool result = is_not_resize && is_inside_unit && !is_inside_current_border;
  
    return ( is_not_resize && is_inside_unit && !is_inside_current_border);    
}

void ImagePlatter::on_unit_clicked(ImagePlatterType::UnitData& unit) {
    auto mouse_pos = ImGui::GetMousePos();
    state.current_unit = &unit;
    auto& move_state = state.move_state;
    move_state.object_start_pos   = unit.transform.position;
    move_state.start_click_pos    = mouse_pos;
    move_state.is_dragging        = true;    
    move_state.some_clicked       = true;
    debug("{}\n", unit.key);
}

void ImagePlatter::update_border() {
    calculate_and_update_unit_rect_pos(state.rect_vertex,*state.current_unit); 
}

void ImagePlatter::do_resize() {
    auto& t = state.current_unit->transform;
    auto mouse_pos = ImGui::GetMousePos();
    auto delta_mouse = mouse_pos - state.resize_state.start_click_pos;
    auto fixed_pos = state.resize_state.fixed_pos;
    ImVec2 delta = state.resize_state.move_pos+delta_mouse-fixed_pos;
    float cc=cosf(t.rotation),ss=sinf(t.rotation);
    ImVec2 f1={cc,ss},f2={-ss,cc};
    ImVec2 new_size=ImVec2{ abs(dot(f1,delta)),abs(dot(f2,delta))}-ImVec2{10,10};
    t.size=new_size;
    t.position=ImVec2{(fixed_pos+mouse_pos)*ImVec2{0.5f,0.5f}}-state.start_pos;
    update_border();
}
