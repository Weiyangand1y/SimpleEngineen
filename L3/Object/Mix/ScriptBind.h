#pragma once
#include "L1/Object/ScriptObject.h"
#include "L3/Object/SceneTreeCore/Sprite2D.h"
#include "L3/Object/SceneTreeCore/Scene.h"


std::any build_info(const sol::object& obj) {
    if(obj.is<int>()){
        auto r=std::any(obj.as<int>());
        std::cout << "known Type: " << r.type().name() << std::endl;
        return r;
        }
    if(obj.is<float>())return std::any(obj.as<float>());
    if(obj.is<std::string>())return std::any(obj.as<std::string>());
    return std::any(0);
}


// bind class
//reference, mean we can append function in scene or app
void script_bind_class(sol::state& script){
    //sol::table result=script.create_table();
    script.set_function("get_info", [&script](Info& info) {
        
        sol::table result=script.create_table();
        
        int index = 1;
        for (const auto& value : info) {            
            // 根据 std::any 的类型，将值放入 Lua table 中
            if (value.type() == typeid(int)) {
                result[index++] = std::any_cast<int>(value);
            } else if (value.type() == typeid(float)) {
                result[index++] = std::any_cast<float>(value);
            } else if (value.type() == typeid(std::string)) {
                result[index++] = std::any_cast<std::string>(value);
            } else {
                std::cout << "Unknown Type: " << value.type().name() << std::endl;
                // 其他类型处理
                result[index++] = "Unsupported Type";
            }
        }
        
        return result;
    });
    
    script["make_info"]=[](sol::variadic_args args)->Info{
        Info info;
        for (auto& arg : args) {
            
            info.push_back(build_info(arg.as<sol::object>()));
        }
        return info;
    };
    script.new_usertype<SignalObject>("SignalObeject",
        "connect",  &SignalObject::connect,
        "emit",     static_cast<void(SignalObject::*)(std::string signal_name,const Info&)>(&SignalObject::emit)
    );
    script.new_usertype<SceneNode>("SceneNode",
        "set_name",         &SceneNode::set_name,
        "signal",           &SceneNode::signal,
        "queue_free",       &SceneNode::queue_free,
        "connect_signal",   &SceneNode::make_signal_record,
        "add_child",        &SceneNode::add_child
    );
    script.new_usertype<Node2D>("Node2D",
        "set_position",     &Node2D::set_position,
        "set_who_to_follow",&Node2D::set_who_to_follow,
        sol::base_classes,sol::bases<SceneNode>()
    );
    script.new_usertype<Sprite2D>("Sprite2D",
    sol::constructors<Sprite2D>(),
    "enter_scene",      &Sprite2D::enter_scene,
    "set_texture",      &Sprite2D::set_texture,    
    "set_scale",        static_cast<void(Sprite2D::*)(float)>(&Sprite2D::set_scale),
    sol::base_classes, sol::bases<Node2D,SceneNode>()
    );
    script.new_usertype<Scene>("Scene",
    "do_queue_free",    &Scene::do_queue_free
    );
}

void script_make_simple(sol::state& script){
    
}
void bind(sol::state& script){
    script_bind_class(script);
    script_make_simple(script);
}