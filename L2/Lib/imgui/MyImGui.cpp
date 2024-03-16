#include "MyImGui.h"
#include "iostream"
#include <GLFW/glfw3.h>
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
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    io.Fonts->AddFontFromFileTTF(
        "C:\\Users\\21wyc\\Desktop\\STZHONGS.TTF", 18, nullptr,
        io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
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
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }


}
MyImGui::MyImGui() {}

void MyImGui::render() {
    
//------------------------------------
   
    ImGui::Begin("Test");
    
    ImGui::InputText("输入",text,20);
    ImGui::End();
//--------------------------------------------------
    
}
