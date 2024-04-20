#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "L2/Lib/imgui/MyImGui.h"
#include "L2/Object/IDPool.h"
#include "ImagePlatterCommand.h"
#include "ImagePlatterType.h"
class ImagePlatter{
friend class ImagePlatterCommand;
private:
    std::vector<std::shared_ptr<Command>> undo_list;
    std::vector<std::shared_ptr<Command>> redo_list;
    IDPool id_pool;
    
    struct MoveState{
        ImVec2 start_click_pos;
        ImVec2 object_start_pos;
        bool is_dragging=false;
        bool some_clicked=false;
    };
    struct ReSizeState{
        ImVec2 fixed_pos;
        ImVec2 move_pos;
        ImVec2 start_click_pos;
        bool is_dragging=false;
        bool some_clicked=false;
    };
    struct State{
        ImVec2 start_pos;
        UnitData* current_unit=nullptr;
        MoveState move_state;
        ReSizeState resize_state;
        ImVec2  rect_vertex[4];
        char input_text[64]={0};
    };
    std::unordered_map <int,UnitData> list; //<id, unit_data>
    std::vector        <ZindexPair>   list2;//<z-index, id> need sort before
    ImageDB* image_db=nullptr;    
    State state;
    void sort_unit_by_z_index();
    void set_z_index(int id,int z_index);
    void drop_to_here();
    void draw_image(UnitData& unit,const ImVec2& target_pos);
    void calculate_and_update_unit_rect_pos(ImVec2 vertex[4],UnitData& unit);
    void handle_border(UnitData& unit);
    bool is_inside_unit_rect(const ImVec2& mouse_pos, UnitData& unit);
    void save_to_db();
    int  add_unit(const std::string& key, ImageType type,const Transform& transform);
    void load_scene_from_db();
    bool on_control_point_pre(const ImVec2& point);
    void draw_border();

    void start_canvas();
    void preccess_input_from_canvas();
    void on_canvas_pressed();
    void on_canvas_released();
    void on_canvas_dragging();
    void draw_canvas();

    void update_control_area();
    void update_canvas();
    bool on_unit_clicked_pre(ImagePlatterType::UnitData& unit);
    void on_unit_clicked(ImagePlatterType::UnitData& unit);
    void update_border();

    void do_resize();
public:
    ImagePlatter();
    void init(ImageDB* p_image_db);   
    void load_from_db();
    void render();   
};

