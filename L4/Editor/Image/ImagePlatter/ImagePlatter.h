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
    //--------------------------------------------------------------------------------
    //[state struct]

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
    //--------------------------------------------------------------------------------
    //[member]

    std::vector<std::shared_ptr<Command>> undo_list;
    std::vector<std::shared_ptr<Command>> redo_list;
    IDPool id_pool;
    std::unordered_map <int,UnitData> list; //<id, unit_data>
    std::vector        <ZindexPair>   z_index_record;//<z-index, id> need sort before
    ImageDB* image_db=nullptr;    
    State state;
    //--------------------------------------------------------------------------------
    //[caculate]

    //check mouse pos if on the unit rect
    bool is_inside_unit_rect(const ImVec2& mouse_pos, UnitData& unit);
    //check mouse pos if on the control point
    bool on_control_point_pre(const ImVec2& point);
    //more complex, decide if need to move to advoid some unexpected situation
    bool check_if_to_move(ImagePlatterType::UnitData& unit);
    //--------------------------------------------------------------------------------
    //[set data: target data]

    //sort by z-index
    void sort_unit_by_z_index();
    void set_z_index(int id,int z_index);
    int  add_unit(const std::string& key, ImageType type,const Transform& transform);
    void do_move();
    void do_resize();
    //db
    void save_scene_to_db();   
    void load_scene_from_db();
    //--------------------------------------------------------------------------------
    //[set data: to set state]

    //the unit rect is some bigger the unit, show rect frame
    void calculate_and_update_unit_rect_pos(ImVec2 vertex[4],UnitData& unit);
    //check if need to resize, yes, set resize state
    //the function need to separate to two part, one is to check if need to resize, the other is to set resize state
    void handle_control_point(UnitData& unit);
    void on_unit_clicked(ImagePlatterType::UnitData& unit);
    void update_border();
    //--------------------------------------------------------------------------------
    //[set data: to call render]
    
    void drop_to_here();
    // wrap function to draw image
    void draw_image(UnitData& unit,const ImVec2& target_pos);      
    void draw_border();
    void draw_canvas();
    void change_cursor_shape_hover_control_point();

    //--------------------------------------------------------------------------------
    //[prosedure]

    //init, sort z-index, set state of start_pos
    void start_canvas();

    void preccess_input_from_canvas();
    void on_canvas_pressed();
    void on_canvas_released();
    void on_canvas_mouse_moving();


    void on_dragging();

    void update_control_area();
    void update_canvas();

   public:
    ImagePlatter();
    void init(ImageDB* p_image_db);   
    void load_from_db();
    void render();   
};

