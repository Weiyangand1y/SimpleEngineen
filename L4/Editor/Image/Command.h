#pragma once
//do undo
class Command{
public:
    virtual void excute()=0;
    virtual void undo()=0;
};
//
class AddCommand:public Command{

};

class DeleteCommand:public Command{

};

class MoveCommand:public Command{

};

class ScaleCommand:public Command{

};

class RotateCommand:public Command{

};

class SetZindexCommand:public Command{

};