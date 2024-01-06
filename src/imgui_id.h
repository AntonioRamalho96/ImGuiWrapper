#pragma once

#include "third_party/imgui/imgui.h"
#include <string>

class ImGuiWrapperId
{
public:
    ImGuiWrapperId(void *id) { ImGui::PushID(id); }
    ImGuiWrapperId(const ImGuiWrapperId &other) = delete;
    ImGuiWrapperId(ImGuiWrapperId &&other) = delete;
    ~ImGuiWrapperId() { ImGui::PopID(); }
};