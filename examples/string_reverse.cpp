#include "imgui_wrapper.h"

class StringReverseGui : public ImGuiWrapper
{
public:
    void GuiDefinition() override
    {
        ImGui::Begin("Reverser");

        ImGuiWrapper::InputText("To reverse", form_string);
        if (ImGui::Button("Reverse"))
            Reverse();

        ImGui::Text("Result: %s", reversed_string.c_str());
        ImGui::End();
    }

private:
    std::string form_string;
    std::string reversed_string{};

    void Reverse()
    {
        reversed_string.clear();
        for (int i = form_string.size() - 1; i >= 0; i--)
            reversed_string.push_back(form_string[i]);
    }
};

int main()
{
    StringReverseGui gui{};
    gui.Loop();
}