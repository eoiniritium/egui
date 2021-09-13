# egui
Gui element library using raylib for drawing

Author: Eoin Mag Ualghairg

## How to use
run `g++ -c include/egui.hpp egui.a -O2 -Wall -Wno-missing-braces -I raylib/include -L raylib/lib/ -lraylib -lopengl32 -lgdi32 -lwinmm` and `ar rvs egui.a include/egui.hpp.gch` in [`egui/code/egui`](code/egui) or run the makefile in [`egui/code/egui`](code/egui).

to use with your project run `g++ main.cpp -o main.exe -O2 --static -static-libgcc -static-libstdc++ -Wall -Wno-missing-braces -I egui/raylib/include -L egui/raylib/lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -I egui/include -L egui/` in the same level as [`main.cpp`](code/main.cpp) is in [`egui/code`](code)

## Writing code
Everything is defined in [`egui/code/egui/include/egui.hpp`](code/egui/include/egui.hpp) and [`cheatsheet.txt`](cheatsheet.txt) defines all the classes, methods and parameters in an easy to read format.
