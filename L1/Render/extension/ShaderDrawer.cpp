#include "ShaderDrawer.h"
#include "L1/App/Config.h"
ShaderDrawer::ShaderDrawer() {}

void ShaderDrawer::set_render(Render& p_renderer) {
    renderer=&p_renderer;
    std::string base_path=Config::getInstance().get("shader_base_path")+"shadertoy/";
    renderer->get_shader_db().load_from_file("pa",base_path+"common.vert",base_path+"particles.frag");
}

void ShaderDrawer::draw(float* transform_mat, float time) {   
    renderer->use_vertex(Render::VertexType::RECT);
    Shader s=renderer->get_shader("pa");
    s.use();
    s.setMat4("transform",transform_mat);
    s.setFloat3("iResolution",1.f,1.f,1.f);
    s.setFloat("iTime",time);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
