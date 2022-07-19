default:
	g++ -c include/egui.hpp egui.a -O2 -Wall -Wno-missing-braces -I raylib/include -L raylib/lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
	ar rvs egui.a include/egui.hpp.gch