#include "L2/Lib/imgui/MyImGui.h"
#include "L1/Render/Renderer.h"
class ImgageLoad{
    struct ImageLoadData{
        char path_text[128]={0};
        char key_text[64]={0};
        int texture_id=-1;
        float texture_aspect_radio=-1.f;
    };
    ImageLoadData data;
    Render* renderer=nullptr;
public:
    ImgageLoad(){}
    void set_renderer(Render* p_renderer){renderer=p_renderer;}
    void save_and_flush(){
        renderer->get_texture_db().load(std::string(data.key_text),std::string(data.path_text));
        Texture& texture=renderer->get_texture(std::string(data.key_text));
        data.texture_id=texture.get_id();
        data.texture_aspect_radio=(float)texture.w/texture.h;
    }
    void render(){       
    ImGui::Begin("Image Load");
        float window_width=ImGui::GetWindowWidth();
        auto& io=ImGui::GetIO();
        ImGui::Text("path:");
        ImGui::SetNextItemWidth(window_width-20);
        ImGui::InputText("##path",data.path_text,sizeof(data.path_text));
        ImGui::Text("key:");
        ImGui::InputText("##key",data.key_text,sizeof(data.key_text));
        if(ImGui::Button("Load Image")){
            save_and_flush();
        }
        if(data.texture_id!=-1){
            ImGui::SeparatorText("Image");            
            ImGui::Image(
                (void*)(intptr_t)data.texture_id,
                {window_width-20,window_width/data.texture_aspect_radio},
                {0,1},{1,0}
            );
        }
        if(ImGui::IsWindowFocused()&&io.KeyCtrl&&ImGui::IsKeyPressed(ImGuiKey_S)){
            save_and_flush();
        }
    ImGui::End();
    }
};