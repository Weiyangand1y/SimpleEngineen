#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "L2/Lib/imgui/MyImGui.h"
#include "L2/Object/IDPool.h"
#include "ImageDB.h"
#include "Command.h"
class ImagePlatter{
private:
    std::vector<std::shared_ptr<Command>> undo_list;
    std::vector<std::shared_ptr<Command>> redo_list;
    IDPool id_pool;
    struct Transform{
        ImVec2 position={350,150};
        ImVec2 size={-1,-1};
        float rotation=0.f;
        int z_index=0;
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
    struct MoveState{
        ImVec2 start_click_pos;
        ImVec2 object_start_pos;
        bool is_dragging=false;
        bool some_clicked=false;
    };
    struct ReSizeState{
        ImVec2 fixed_pos;
        ImVec2 move_pos;
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
    std::unordered_map <int,UnitData> list;//<id, unit_data>
    std::vector        <ZindexPair>   list2;        //<z-index, id> need sort before
    ImageDB* image_db=nullptr;    
    State state;
    void sort_unit_by_z_index();
    void set_z_index(int id,int z_index);
    void drop_to_here();
    void draw_image(UnitData& unit,const ImVec2& target_pos);
    void calculate_rect(ImVec2 vertex[4],UnitData& unit);
    void handle_border(UnitData& unit);
    bool is_inside_unit_rect(const ImVec2& mouse_pos,const ImVec2& target_pos,UnitData& unit);
    void save_to_db();
    int  add_unit(const std::string& key, ImageType type,const Transform& transform);
    void load_scene_from_db();
    void handle_control_point(const ImVec2& point);
    void draw_border();
public:
    void init(ImageDB* p_image_db);
    ImagePlatter();
    void load_from_db();
    void render();
    void handle_canvas_clicked(ImVec2& target_pos,ImagePlatter::UnitData& unit);

   private:
    class AddCommand : public Command {
        std::string key;
        ImageType type;
        ImVec2 pos;
        ImagePlatter* env;

        int id;  // to delete
       public:
        AddCommand(std::string key,
                   ImageType type,
                   ImVec2 pos,
                   ImagePlatter* env);
        void execute() override;
        void undo() override;
    };

class DeleteCommand:public Command{
    int id;
    ImagePlatter* env;
    UnitData data;
public:
    DeleteCommand(int id,ImagePlatter* env);
    void execute()override;
    void undo()override;
};

class MoveCommand:public Command{

};

class ScaleCommand:public Command{

};

class RotateCommand:public Command{

};

class SetZindexCommand:public Command{

};
};

