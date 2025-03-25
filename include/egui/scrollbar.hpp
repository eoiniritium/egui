#include "raylib.h"
#include "egui.hpp"

#include <iostream>

namespace egui {
    class Scrollbar: public UIComponent {
        public:
        int scrollLength;
        Pair<int> scroll;
        Pair<int> grabberPosition;
        Pair<int> grabberSize;

        Color fgColour, bgColour;

        enum Orientation {
            Vertical,
            Horizontal
        };

        struct Options {
            Pair<int> position;
            Pair<int> size;
            int scrollLength;
            Color bgColour = LIGHTGRAY;
            Color fgColour = DARKGRAY;

        };

        Scrollbar(Options options) : 
        UIComponent(
            options.position,
            options.size
        ) {
            grabberSize.x = size.x;
            grabberSize.y = size.y / scrollLength;
            grabberPosition = position;

            this->bgColour = bgColour;
            this->fgColour = fgColour;
        }

        void onPress(onEventCallback _) override {
            int mouseY = GetMouseY();

            grabberPosition.y = mouseY - grabberSize.y/2;
        }

        Pair<int> getScroll() {
            return scroll;
        }

        void draw(Pair<int> _) override {
            DrawRectangle(position.x, position.y, size.x, size.y, bgColour);

            std::cout << grabberSize.y;
            DrawRectangle(grabberPosition.x, grabberPosition.y, grabberSize.x, grabberSize.y, fgColour);
        }
    };
}