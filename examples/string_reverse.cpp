#include "imgui_wrapper.h"

class StringReverseGui : public ImGuiWrapper
{
public:
    void GuiDefinition() override
    {
        ImGui::Begin("Reverser");
        
        ImGui::InputText("To reverse", form_string, 100);
        if(ImGui::Button("Reverse"))
            Reverse();

        ImGui::Text("Result: %s", reversed_string.c_str());
        ImGui::End();
    }

private:
    char form_string[100];
    std::string reversed_string{};

    void Reverse()
    {
        std::string input(form_string);
        reversed_string.clear();
        for(int i = input.size() - 1; i >= 0; i--)
            reversed_string.push_back(input[i]);
    }
};

int main()
{
    StringReverseGui gui{};
    gui.Loop();
}