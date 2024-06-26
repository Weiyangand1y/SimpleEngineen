#include "ImagePlatterCommand.h"
#include "ImagePlatter.h"
#include "L1/Debug/Log.h"
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
    env->z_index_record.erase(std::remove_if(env->z_index_record.begin(),env->z_index_record.end(),
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
    env->z_index_record.erase(std::remove_if(env->z_index_record.begin(),env->z_index_record.end(),
                        [&](const auto& e){return e.id==id;})
                    );
    env->id_pool.releaseID(id);
    env->state.selected_unit = nullptr;
}

void ImagePlatterCommand::DeleteCommand::undo() {
    env->add_unit(data.key, data.sub_key == "" ? ImageType::MainImage : ImageType::SubImage, data.transform);
}