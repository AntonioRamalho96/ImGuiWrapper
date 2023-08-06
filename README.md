# ImguiWrapper

The wrapper uses the following third party software (copy pasted to this repo):
 - [Dear Imgui](https://github.com/ocornut/imgui)
 - [Dear Imgui File Dialog](https://github.com/aiekick/ImGuiFileDialog)

This wrapper provides a parent class that enables to easily create your GUI.
To do so you just need to extend the *ImGuiWrapper* class and focus on your GUI. 
No need for initializations, no need to close contexts, all of that is implemented in *ImGuiWrapper*.

Here is an example on how make a GUI that reverses a string:

![alt text](https://github.com/AntonioRamalho96/ImGuiWrapper/blob/main/doc_material/Screenshot%20from%202023-08-06%2013-18-10.png)

And as you see, the code is quite simple!

```c++
#include "imgui_wrapper.h"

class StringReverseGui : public ImGuiWrapper
{
public:
    void GuiDefinition() override
    {
        ImGui::Begin("Reverser");                            // Opens a window named Reverser
        
        ImGui::InputText("To reverse", form_string, 100);    // Created a text prompt for the input
        if(ImGui::Button("Reverse"))                         // Creates a button that when triggered...
            Reverse();                                       // ... computes the result

        ImGui::Text("Result: %s", reversed_string.c_str());  // Display the result
        ImGui::End();                                        // Determine the end of the window
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
```

We have also included a nice simplefile prompt. Here is an example using it


## Dependencies
The project depends on SDL2 and opengl, to install them use:
```shell
sudo apt install libsdl2-dev freeglut3-dev
```

## Clone it, compile it and see the examples
To gice it a try the project already comes with a CMakeLists.txt file to allow easy compilation with cmake.
If you have g++ and cmake you should be able to compile the project as follows:

```
git clone https://github.com/AntonioRamalho96/ImGuiWrapper.git
cd ImGuiWrapper
mkdir build
cd build
cmake ..
make
```

Now, the example executables are in ${ImGuiWrapperDir}/build/examples

Here is an example on how to run an example:
```shell
# In ImGuiWrapper directory
./build/examples/string_reverse
``` 

## Use ImguiWrapper in your code
Basically to use *ImguiWrapper* you just need to:
 - Include its header (located at ${ImguiWrapperDir}/src/imgui_wrapper.h)
 - link against its static library (after building is at ${ImguiWrapperDir}/build/src/libimgui_wrapper.a)
 - Link against SDL2, dl and opengl
Here are several ways to do so:

### Terminal
For this you must first clone and compile the project, as described in [Clone it, compile it and see the examples](#clone-it-compile-it-and-see-the-examples).

If you compile your executable in the terminal just do it as such:
```shell
g++ -I ${ImguiWrapperDir}/src your_executable.cpp -L ${ImguiWrapperDir}/build/src -limgui_wrapper -lSDL2 -lGL -ldl 
```
As you might know:
 - **g++** - is a C++ compiler
 - **-I \$\{ImguiWrapperDir\}/src** - tells the compiler to search for the headers at ${ImguiWrapperDir}/src
 - **-L \$\{ImguiWrapperDir\}/build/src -limgui_wrapper** - tells the linker to search for libraries at ${ImguiWrapperDir}/build/src, and then links to 
 - **-lSDL2 -lGL -ldl** - links the executable to SDL2, dl and open_gl

 ### Makefile
 For this you must first clone and compile the project, as described in [Clone it, compile it and see the examples](#clone-it-compile-it-and-see-the-examples).

 Well, basically the same as terminal more or less, here is an example:
 ```Makefile
INCLUDE_FLAGS=-I ../src
LINKAGE_FLAGS=-L ../build/src -limgui_wrapper -lSDL2 -lGL -ldl

your_executable: your_executable.cpp
	g++ ${INCLUDE_FLAGS} $^ -o $@ ${LINKAGE_FLAGS}
```

### CMake
As the directory already includes CMake files, you dont need to pre-compile the library.
You can simply place the \$\{ImguiWrapperDir\} in your project folder and add it as a subfolder.
You don't even need to explicitly link SDL2, dl and open_gl, our CMakeLists already do so.

So, here is an example, imagine you are in your cmake source dir, place *ImguiWrapper* directory inside of it, as such

```
- your_source_dir
  |- ImguiWrapper
  |- your_executable.cpp
  |- CMakeLists.txt
```

That CMakeLists.txt can be as such:
```cmake
add_subdirectory(ImguiWrapper)
include_directories(ImguiWrapper/src)
add_executable(your_executable your_executable.cpp)
target_link_libraries(your_executable imgui_wrapper)
```