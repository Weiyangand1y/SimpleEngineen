#include "ImagePlatterCommand.h"
#include "ImagePlatter.h"

ImagePlatterCommand::AddCommand::AddCommand(std::string key,ImageType type,ImVec2 pos,ImagePlatter* env)
    :env(env),pos(pos),key(key),type(type){}

void ImagePlatterCommand::AddCommand::execute() {
    int return_id=env->add_unit(key,type,{pos});
    if(return_id==-1)Logger::log(8,"AddCommand failed");
    id=return_id;
}

void ImagePlatterCommand::AddCommand::undo() {
    debug("undo\n");
    env->list.erase(id);
    env->list2.erase(std::remove_if(env->list2.begin(),env->list2.end(),
                        [&](const auto& e){return e.id==id;})
                    );
    env->id_pool.releaseID(id);
}

ImagePlatterCommand::DeleteCommand::DeleteCommand(int id, ImagePlatter* env) {
    this->id = id;
    this->env = env;
    data = env->list[id];   
}

void ImagePlatterCommand::DeleteCommand::execute() {
    env->list.erase(id);
    env->list2.erase(std::remove_if(env->list2.begin(),env->list2.end(),
                        [&](const auto& e){return e.id==id;})
                    );
    env->id_pool.releaseID(id);
    env->state.current_unit = nullptr;
}

void ImagePlatterCommand::DeleteCommand::undo() {
    env->add_unit(data.key, data.sub_key == "" ? ImageType::MainImage : ImageType::SubImage, data.transform);
}