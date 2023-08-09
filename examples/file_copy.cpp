#include "imgui_wrapper.h"
#include <fstream>
class FileCopyGui : public ImGuiWrapper
{
public:
    void GuiDefinition()
    {
        ImGui::Begin("File Copy");

        FileDialog("Input", "((.*))", input_file);
        ImGui::Text("In: %s", input_file.c_str());
        FileDialog("Output", "((.*))", output_file);
        ImGui::Text("Out: %s", output_file.c_str());
        if(ImGui::Button("Copy"))
            Copy();
        
        ImGui::End();
    }

private:
    std::string input_file{};
    std::string output_file{};

    void Copy()
    {
        std::ifstream in(input_file);
        std::ofstream out(output_file);
        std::string line;
        while(std::getline(in, line))
            out << line << std::endl;
    }
};

int main()
{
    FileCopyGui().Loop();
}