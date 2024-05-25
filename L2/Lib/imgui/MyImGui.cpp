#include "MyImGui.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include "L1/App/Config.h"
#include "L1/Debug/Log.h"
#include "imgui_internal.h"
int MyImGui::count =10;
std::unordered_map<std::string, ImFont*> MyImGui::font_map;
void load_font_file(){
    ImGuiIO& io = ImGui::GetIO();

    MyImGui::font_map["text"]=io.Fonts->AddFontFromFileTTF(
            Config::getInstance().get("font_path").c_str(),
            20, nullptr,
            io.Fonts->GetGlyphRangesChineseSimplifiedCommon()
        );                           
    MyImGui::font_map["large"]=io.Fonts->AddFontFromFileTTF(
            Config::getInstance().get("font_path").c_str(),
            40, nullptr,
            io.Fonts->GetGlyphRangesChineseSimplifiedCommon()
        );
}

void set_style(){
    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text]                   = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
    colors[ImGuiCol_WindowBg]               = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.93f, 0.96f, 0.93f, 0.94f);
    colors[ImGuiCol_Border]                 = ImVec4(0.00f, 0.00f, 1.00f, 0.50f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.94f, 0.87f, 0.87f, 0.00f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.52f, 0.87f, 0.76f, 0.54f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.83f, 0.90f, 0.98f, 0.40f);
    colors[ImGuiCol_TitleBg]                = ImVec4(0.87f, 1.00f, 0.95f, 1.00f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.72f, 1.00f, 0.72f, 1.00f);
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.21f, 0.42f, 0.13f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.77f, 0.96f, 0.69f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.16f, 0.37f, 0.17f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.20f, 0.37f, 0.09f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.57f, 0.82f, 0.54f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.19f, 0.46f, 0.82f, 1.00f);
    colors[ImGuiCol_Button]                 = ImVec4(0.63f, 0.60f, 0.9f, 0.9f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.7f, 0.7f, 0.99f, 0.9f);
    colors[ImGuiCol_ButtonActive]          = ImVec4(0.78f, 0.78f, 0.99f, 0.9f);
    colors[ImGuiCol_Separator]              = ImVec4(0.47f, 0.47f, 0.92f, 0.50f);

    colors[ImGuiCol_Tab]                    = ImVec4(0.91f, 0.99f, 0.84f, 0.86f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.72f, 0.98f, 0.77f, 0.80f);
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.50f, 0.82f, 0.99f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.50f, 0.72f, 0.89f, 1.00f);

    colors[ImGuiCol_TabActive]              = ImVec4(0.50f, 0.82f, 0.99f, 1.00f);

}
void MyImGui::static_init(GLFWwindow* window) {    
    const char* glsl_version = "#version 130";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();//io是单例，用到了用这个方法
    (void)io;
    //io.FontGlobalScale = 1.2f;
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
    set_style();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    load_font_file();
}

ImFont* MyImGui::get_imfont(int index){
    ImFontAtlas* fontAtlas = ImGui::GetIO().Fonts;
    int numFonts = fontAtlas->Fonts.Size;
    if(index>=numFonts)return nullptr;
    return fontAtlas->Fonts[index];
}

void MyImGui::static_begin() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    
}
void MyImGui::static_end() {
    // Rendering
    
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
    //
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable){
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
    }


}
MyImGui::MyImGui() {}

void MyImGui::render() {}

void ImGui::ImageRotated(ImTextureID tex_id, ImVec2 center, ImVec2 size, float angle,ImVec4 uv) {
    
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    float cos_a = cosf(-angle*(3.14159f/180.f));
    float sin_a = sinf(-angle*(3.14159f/180.f));
    ImVec2 pos[4] =
    {
        center + ImRotate(ImVec2(-size.x * 0.5f, -size.y * 0.5f), cos_a, sin_a),
        center + ImRotate(ImVec2(+size.x * 0.5f, -size.y * 0.5f), cos_a, sin_a),
        center + ImRotate(ImVec2(+size.x * 0.5f, +size.y * 0.5f), cos_a, sin_a),
        center + ImRotate(ImVec2(-size.x * 0.5f, +size.y * 0.5f), cos_a, sin_a)
    };
    ImVec2 uvs[4] = 
    { 
        ImVec2(uv.x, uv.z), 
        ImVec2(uv.y, uv.z), 
        ImVec2(uv.y, uv.w), 
        ImVec2(uv.x, uv.w) 
    };

    draw_list->AddImageQuad(tex_id, pos[0], pos[1], pos[2], pos[3], uvs[0], uvs[1], uvs[2], uvs[3], IM_COL32_WHITE);

}

