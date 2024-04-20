#pragma once
#include <string>
#include <vector>
#include "L2/Lib/imgui/MyImGui.h"
#include "L1/Object/ScriptObject.h"
class ImConsole{
    //为了蹭一下文本复制的功能
    struct ColorText{
        unsigned int color;
        std::string text;
    };
    char input[64]={0};
    const int max_count=10;
    std::vector<ColorText> text_list;
    void put_text(int color, const std::string& text){
        ImGui::PushStyleColor(ImGuiCol_Text,color);
        
        ImGui::InputText(("##"+text).c_str(),const_cast<char*>(text.c_str()),text.size(),ImGuiInputTextFlags_ReadOnly);
        ImGui::PopStyleColor();
    }
    ScriptObject so;
public:
    ImConsole(){
        
        text_list.reserve(max_count);
        text_list.push_back({IM_COL32(17,17,64,255),"aabb"});
        text_list.push_back({0xffccaf22,"aabbcc"});
        text_list.push_back({0xffccaf22,""});
    }
    void render(){
        ImGui::Begin("Console");
        ImGui::PushStyleColor(ImGuiCol_FrameBg,0x0);
        for(auto& t:text_list){
            put_text(t.color,t.text);
        }
        ImGui::PopStyleColor();    
        if(ImGui::IsWindowFocused() && ImGui::IsKeyDown(ImGuiKey_Enter)){
            ImGui::SetKeyboardFocusHere();
        }       
        if(ImGui::InputText("##input",input,64,ImGuiInputTextFlags_EnterReturnsTrue)){
            text_list.push_back({IM_COL32(21,34,99,255),">>"+std::string(input)});
            so.script.do_string(input);
        }
        ImGui::SetScrollHereY(1.0f);
        ImGui::End();
    }
};