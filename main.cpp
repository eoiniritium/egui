#include <iostream>
#include <cstring>
#include "raylib.h"
#include "egui/egui.hpp"
#include "egui/label.hpp"
#include <time.h>
#include <stdlib.h>
#include <functional>

#define SCREENX 1280
#define SCREENY 720

int main()
{
    egui::text::Typeface Inter("recources/Inter-variable.ttf", 
        {
            egui::text::h1,
            egui::text::h2,
            egui::text::h3,
            egui::text::h4,
            egui::text::h5,
            egui::text::h6,
            egui::text::normal,
            egui::text::small
        }
    );

    egui::App app("EGUI", {1280, 720}, 144);
    
    egui::text::Text helloWorldText;
    helloWorldText.text = "Hello world";
    helloWorldText.fontSize = egui::text::h1;
    helloWorldText.fontColour = BLACK;
    helloWorldText.font = Inter[egui::text::h1];
    app.addComponent(new egui::Label(helloWorldText, {10, 10}, WHITE));

    app.mainloop();

    return 0;
}