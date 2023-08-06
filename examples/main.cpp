// This example is adapted from a Dear ImGui example:

// Dear ImGui: standalone example application for SDL2 + OpenGL
// (SDL is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#include "imgui_wrapper.h"



class MyInterface : public ImGuiWrapper
{
public:
    void GuiDefinition() override
    {

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Our big window
        MainWindow();

        // 3. Show another simple window.
        if (show_another_window)
            SimpleWindow();
    }

private:
    bool show_demo_window = true;
    bool show_another_window = false;
    float f = 0.0f;
    int counter = 0;
    std::string selected_file = "";

    // My windows
    void MainWindow()
    {
        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.

        ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");          // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &show_demo_window); // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);                        // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float *)&properties.clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / properties.io->Framerate, properties.io->Framerate);


        FileDialog("ChooseFileDlgKey", ".cpp,.h,.hpp", selected_file);
        ImGui::Text("File: %s", selected_file.c_str());

        
        ImGui::End();
    }

    void SimpleWindow()
    {
        ImGui::Begin("Another Window", &show_another_window); // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            show_another_window = false;
        ImGui::End();
    }

};

int main(int, char **)
{
    MyInterface gui{};
    gui.Loop();
}
