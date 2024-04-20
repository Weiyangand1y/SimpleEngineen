#pragma once
#include "../Command.h"
#include "ImagePlatterType.h"
#include "../ImageDB.h"
using namespace ImagePlatterType;
class ImagePlatter;
class ImagePlatterCommand{
public:
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



}; // namespace ImagePlatter
