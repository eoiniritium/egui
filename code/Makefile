default:
	g++ main.cpp -o main.exe --static -static-libgcc -static-libstdc++ -Wall -Wno-missing-braces -I egui/raylib/include -L egui/raylib/lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -I egui/include -L egui/
	./main.exe

darwin:
	clang++ -std=c++11 main.cpp `pkg-config --libs --cflags raylib` -o main -I egui/include -L egui/
	./main