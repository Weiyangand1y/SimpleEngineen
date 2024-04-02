#include "MyImGui.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include "L1/App/Config.h"
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
    colors[ImGuiCol_Button]                 = ImVec4(0.91f, 1.00f, 0.66f, 0.77f);
    colors[ImGuiCol_Separator]              = ImVec4(0.47f, 0.47f, 0.92f, 0.50f);
    colors[ImGuiCol_Tab]                    = ImVec4(0.71f, 0.99f, 0.84f, 0.86f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.72f, 0.98f, 0.77f, 0.80f);
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
    ImGui::StyleColorsLight();

    set_style();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    io.Fonts->AddFontFromFileTTF(Config::getInstance().get("font_path").c_str(),
                                24, nullptr,
                                io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
    io.Fonts->AddFontFromFileTTF(Config::getInstance().get("font_path").c_str(),
                                48, nullptr,
                                io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
    
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
