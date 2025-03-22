#pragma once
#include "raylib.h"
#include "egui.hpp"
#include <string>

namespace egui {
    class Label: public UIComponent {  
        public:
        text::Text text;
        Color bgColour;
        Pair<int> padding;
        
        public:
        Label (
            text::Text text,
            Pair<int> position, 
            Color bgColour,
            Pair<int> padding = {0, 0}
        ) : UIComponent(
            position,
            {
                (2 * padding.x) + MeasureText(text.text.c_str(), text.fontSize),
                (2 * padding.y) + static_cast<int>(text.fontSize)
            }
        ) {
            this->text = text;
            this->bgColour = bgColour;
            this->padding = padding;
        }

        void draw(Pair<int> scrolled) override {            
            DrawRectangle(
                position.x, position.y, 
                size.x, size.y, bgColour
            );
            DrawText(
                text.text.c_str(), 
                position.x + padding.x,
                position.y + padding.y,
                text.fontSize,
                text.fontColour
            );
        }

        void onClick() override {

        }
    };

}