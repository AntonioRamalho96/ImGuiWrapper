
#include "third_party/imgui/imgui.h"
#include "third_party/imgui/backends/imgui_impl_sdl2.h"
#include "third_party/imgui/backends/imgui_impl_opengl3.h"
#include "third_party/imgui_file_dialog/ImGuiFileDialog.h"
#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>

struct ImGuiWrapperConfigs
{
    std::string window_name = "ImGui Wrapper";
    int window_x = SDL_WINDOWPOS_CENTERED;
    int window_y = SDL_WINDOWPOS_CENTERED;
    int window_w = 1280;
    int window_h = 720;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    bool style_dark = true;
};

struct ImGuiWrapperProperties
{
    ImGuiIO *io;
    ImVec4 clear_color;
    SDL_Window *window;
    SDL_Event event;
    SDL_GLContext gl_context;
    bool done = false;
};

class ImGuiWrapper
{
public:
    ImGuiWrapper();
    explicit ImGuiWrapper(const ImGuiWrapperConfigs &configs);

    virtual void Loop();

    // Draw it in the child method
    virtual void GuiDefinition() = 0;

    virtual ~ImGuiWrapper();

protected:
    ImGuiWrapperProperties properties{};

    void FileDialog(const std::string &name, const std::string &extensions, std::string &file_path) const;
    
    void NewFrame();

    void RenderFrame();

private:
    int InitSdl();
};