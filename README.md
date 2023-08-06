# ImguiWrapper

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

## Clone compile it and see the examples
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