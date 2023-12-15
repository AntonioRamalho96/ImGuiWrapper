#pragma once

#include "third_party/imgui/imgui.h"
#include <string>

class ImGuiId
{
public:
    ImGuiId(void *id) { ImGui::PushID(id); }
    ImGuiId(const ImGuiId &other) = delete;
    ImGuiId(ImGuiId &&other) = delete;
    ~ImGuiId() { ImGui::PopID(); }
};