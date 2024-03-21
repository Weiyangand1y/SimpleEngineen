#include "MyImGui.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include "L1/App/Config.h"

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

    ImGuiStyle* style = &ImGui::GetStyle();
    ImVec4* colors = style->Colors;
    colors[ImGuiCol_TitleBgActive] = ImColor(0xffb3a7fa);
    colors[ImGuiCol_ScrollbarBg]=ImVec4(0.93f, 0.23f, 0.30f, 0.80f),
    colors[ImGuiCol_ScrollbarGrab]=ImVec4(0.93f, 0.93f, 0.60f, 0.80f),
    colors[ImGuiCol_ScrollbarGrabHovered]=ImVec4(0.43f, 0.73f, 0.80f, 0.80f),
    colors[ImGuiCol_ScrollbarGrabActive]=ImVec4(0.43f, 0.53f, 0.10f, 0.80f),
    colors[ImGuiCol_Button]=ImColor(0xe9b9aaff);
    colors[ImGuiCol_ButtonHovered]=ImColor(0xd98481ff);
    colors[ImGuiCol_ButtonActive]=ImColor(0xeea8abff);
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
