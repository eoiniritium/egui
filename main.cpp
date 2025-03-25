#include <iostream>
#include <cstring>
#include "raylib.h"
#include "egui/egui.hpp"
#include "egui/label.hpp"
#include "egui/scrollbar.hpp"
#include <time.h>
#include <stdlib.h>
#include <functional>

void testFunc() {
    std::cout << "Test" << std::endl;
}

int main()
{
    egui::Pair<int> screen;
    screen.x = 1280;
    screen.y = 720;

    egui::App::Options options;
    options.windowName = "EGUI";
    options.dimensions = {1280, 720};
    egui::App app(options);

    egui::text::Typeface Inter("recources/Inter-variable.ttf", 
        {
            egui::text::h1,
            egui::text::h2,
            egui::text::h3,
            egui::text::h4,
            egui::text::h5,
            egui::text::h6,
            egui::text::normal,
            egui::text::small,
        }
    );

    egui::text::Text helloWorldText;
    helloWorldText.text = "Hello world";
    helloWorldText.fontSize = egui::text::small;
    helloWorldText.fontColour = BLACK;
    helloWorldText.font = Inter[egui::text::small];


    auto hw2 = helloWorldText;
    hw2.text = "Test 2";

    app.addComponent(new egui::Label(helloWorldText, {0, 0}, WHITE));
    app.addComponent(new egui::Label(hw2, {0, 0}, WHITE));

    app.addComponent(new egui::Scrollbar({screen.x - 10, 0}, {10, screen.y}, 10));

    app.mainloop();

    return 0;
}