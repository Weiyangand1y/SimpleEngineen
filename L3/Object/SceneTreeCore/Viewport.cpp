#include "Viewport.h"
#include "L1/App/Config.h"
#include "L1/Debug/Log.h"
#include "Scene.h"
#include "L2/Lib/imgui/MyImGui.h"
Viewport::Viewport() {
    auto [w,h]=Config::getInstance().get_windows_size();
    fb.set_size(w,h);
    fb.create();
    viewport=this;
    signal.connect("click",[](Info info){
        InfoWrapper info_wrap(info);
        float nx,ny;
        info_wrap.next(nx).next(ny);
        debug("click: {:.4f} {:.4f}\t Normalized-Coord\n",nx,ny);
    });
}
void Viewport::set_camera(Camera* p_camera) {
    camera=p_camera;
}

Camera* Viewport::get_camera() {
    return camera;
}

mat4& Viewport::get_transform_mat4() {
    assert(camera);
    return camera->get_transform_mat4();
}

void Viewport::add_child(SceneNode* node) {
    node->set_viewport(this);
    Logger::log(0,"Viewport should put itself to its child\n");
    addChild(node);
    
}
#define FB(X) r->start_framebuffer("f2");\
        r->clear_color();\
        X;\
        r->end_framebuffer();

void Viewport::_after_process(float delta) {
    Render* r=scene->app->get_renderer();
    
    // FB(
    //     Node::_after_process(delta);
    // );
    fb.bind();
    r->clear_color();
    Node::_after_process(delta);
    fb.unbind();
    //drawer->draw_texture(r->get_framebuffer_color_texture_id("f2"),"screen");
    
    FB(drawer->draw_texture(fb.get_color_texture_id(),"screen");)
}
