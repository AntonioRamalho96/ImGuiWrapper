#include "imgui_wrapper.h"

#include <unistd.h>

class HeavyTaskLauncherGui : public ImGuiWrapper
{
public:
    void GuiDefinition() override
    {
        ImGui::Begin("Task Controller");
        ImGui::BeginDisabled(running);
        ImGui::InputInt("Farm Time (s)", &configs.time_s);
        if(ImGui::Button("Start Farming"))
            StartFarming();
        ImGui::EndDisabled();
        ImGui::Text("%s", status.c_str());
        CheckTermination();
        ImGui::End();
    }

private:
    struct Configs
    {
        int time_s{};
    };
    Configs configs{};
    bool running{};
    bool done{};
    std::thread task{};
    std::string status{};

    void StartFarming()
    {
        running = true;
        task = std::thread(&HeavyTaskLauncherGui::Task, this);
        status = "Running...";
    }

    void CheckTermination()
    {
        if(running && done)
        {
            done = false;
            running = false;
            task.join();
            status = "Done!";
        }
    }

    void Task()
    {
        sleep(configs.time_s);
        done = true;
    }
};

int main()
{
    HeavyTaskLauncherGui().Loop();
}