# Create .a file for imgui_wrapper with all necessary dependencies
add_library(${PROJECT_NAME} STATIC  third_party/imgui/imgui.cpp
                                    third_party/imgui/imgui_draw.cpp
                                    third_party/imgui/imgui_demo.cpp
                                    third_party/imgui/imgui_tables.cpp
                                    third_party/imgui/imgui_widgets.cpp
                                    # Backends
                                    third_party/imgui/backends/imgui_impl_sdl2.cpp
                                    third_party/imgui/backends/imgui_impl_opengl3.cpp
                                    # FileExplorer support
                                    third_party/ImGuiFileDialog/ImGuiFileDialog.cpp
                                    # Wrapper Code
                                    imgui_wrapper.cpp)

target_link_libraries(${PROJECT_NAME} SDL2 GL dl)