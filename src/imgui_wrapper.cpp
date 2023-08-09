#include "imgui_wrapper.h"
#include <SDL2/SDL_opengl.h>

ImGuiWrapper::ImGuiWrapper() : ImGuiWrapper(ImGuiWrapperConfigs{})
{
}

ImGuiWrapper::ImGuiWrapper(const ImGuiWrapperConfigs &configs)
{

    if (InitSdl() == -1)
        exit(-1);

    properties.window = SDL_CreateWindow(configs.window_name.c_str(), configs.window_x, configs.window_y, configs.window_w, configs.window_h, configs.window_flags);
    properties.gl_context = SDL_GL_CreateContext(properties.window);
    SDL_GL_MakeCurrent(properties.window, properties.gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    properties.io = &(ImGui::GetIO());
    (void)properties.io;
    properties.io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    properties.io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

    // Setup Dear ImGui style
    if (configs.style_dark)
        ImGui::StyleColorsDark();
    else
        ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    const char *glsl_version = "#version 130";

    ImGui_ImplSDL2_InitForOpenGL(properties.window, properties.gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);

    properties.clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    properties.done = false;
}

void ImGuiWrapper::Loop()
{
    while (!properties.done)

    {
        // Start the Dear ImGui frame
        NewFrame();

        // Draw the graphical interface
        GuiDefinition();

        // Rendering
        RenderFrame();
    }
}

ImGuiWrapper::~ImGuiWrapper()
{
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(properties.gl_context);
    SDL_DestroyWindow(properties.window);
    SDL_Quit();
}

void ImGuiWrapper::FileDialog(const std::string &name, const std::string &extensions, std::string &file_path) const
{
    // open Dialog Simple
    ImGui::PushID(name.c_str());
    if (ImGui::Button("BrowseFile"))
        ImGuiFileDialog::Instance()->OpenDialog(name.c_str(), "Choose File", extensions.c_str(), "." );
    ImGui::PopID();

    // display
    if (ImGuiFileDialog::Instance()->Display(name.c_str()))
    {
        // action if OK
        if (ImGuiFileDialog::Instance()->IsOk())
            file_path = ImGuiFileDialog::Instance()->GetCurrentPath() + "/" + ImGuiFileDialog::Instance()->GetCurrentFileName();

        // close
        ImGuiFileDialog::Instance()->Close();
    }
}

void ImGuiWrapper::NewFrame()
{
    while (SDL_PollEvent(&properties.event))
    {
        ImGui_ImplSDL2_ProcessEvent(&properties.event);
        if (properties.event.type == SDL_QUIT)
            properties.done = true;
        if (properties.event.type == SDL_WINDOWEVENT && properties.event.window.event == SDL_WINDOWEVENT_CLOSE && properties.event.window.windowID == SDL_GetWindowID(properties.window))
            properties.done = true;
    }
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void ImGuiWrapper::RenderFrame()
{
    // Rendering
    ImGui::Render();
    glViewport(0, 0, (int)properties.io->DisplaySize.x, (int)properties.io->DisplaySize.y);
    glClearColor(properties.clear_color.x * properties.clear_color.w, properties.clear_color.y * properties.clear_color.w, properties.clear_color.z * properties.clear_color.w, properties.clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(properties.window);
}

int ImGuiWrapper::InitSdl()
{
    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    // GL 3.0 + GLSL 130
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    // Create window with graphics context
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    return 0;
}