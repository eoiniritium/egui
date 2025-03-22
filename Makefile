default:
	g++ -std=c++20 main.cpp -o main.exe --static -static-libgcc -static-libstdc++ -Wall -Wno-missing-braces -I include/raylib/include -L include/raylib/lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -I include -L include
	./main.exe

darwin:
	clang++ -std=c++20 main.cpp `pkg-config --libs --cflags raylib` -o main -I include
	./main

